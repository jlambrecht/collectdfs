
#include "client.h"

#include <iostream>
#include <sstream>

#include <collectd/client.h>

using collectd_fs::collectd_client;
using std::stringstream;

collectd_client::collectd_client()
{
}

int collectd_client::connect(string address)
{
	return lcc_connect(address.c_str(), &m_handle);
}

string collectd_client::get_stat(string stat_name)
{
	lcc_identifier_t ident;
	size_t ret_values_num;
	double *ret_values;
	stringstream stat_value_ss;

	// TODO: we really need to handle error conditions better here, not just return an empty string
	if (lcc_string_to_identifier(m_handle, &ident, stat_name.c_str())) {
		std::cerr << "Couldn't convert stat name " << stat_name << " to identifier" << std::endl;
		return string("");
	}

	int result = lcc_getval(m_handle,
							&ident, &ret_values_num, &ret_values, NULL);

	if (result != 0 || ret_values_num != 1) {
		std::cerr << "Couldn't get statistic " << stat_name << " from collectd" << std::endl;
		return string("");
	}

	stat_value_ss << ret_values[0];

	free(ret_values);

	return stat_value_ss.str();
}

list<string> collectd_client::get_stat_list()
{
	lcc_identifier_t *stats;
	list<string>      stat_list;
	size_t            num_stats;

	int result = lcc_listval(m_handle, &stats, &num_stats);

	if (result != 0) {
		std::cerr << "Couldn't get list of stats from collectd ("
				  << lcc_strerror(m_handle) << std::endl;
	}
	else
	{
		for (unsigned int i = 0; i < num_stats; i++) {

			char stat_str[MAX_STAT_STR_LEN] = {0};

			result =
				lcc_identifier_to_string(m_handle, stat_str, MAX_STAT_STR_LEN - 1,
             &stats[i]);

			stat_list.push_back(stat_str);
		}

		free(stats);
	}

	return stat_list;
}
