
#include "common.h"
#include "entry.h"
#include <memory>

using namespace collectd_fs;
using collectd_fs::entry;

entry::entry(string token) :
	m_token(token),
	m_last_update_time(0)
{}

entry * entry::clone () const {
	std::unique_ptr<entry> copy (new entry(m_token));
	for(auto sub : m_sub_entries) {
		copy->m_sub_entries.push_back(sub->clone());
	}

	copy->m_complete_stat_name = m_complete_stat_name;
	copy->m_last_update_time = m_last_update_time;
	return copy.release();
}

entry::~entry()
{
	entry_iterator iter;
	
	foreach(iter, m_sub_entries) {
		if (*iter != NULL)
			delete *iter;
	}
}

entry *entry::add_sub_entry(string token)
{
	entry_iterator iter;

	foreach(iter, m_sub_entries) {
		if ((*iter)->m_token == token)
			return *iter;
	}

	entry *new_entry = new entry(token);

	m_sub_entries.push_back(new_entry);
	m_sub_entries.sort();

	return new_entry;
}
