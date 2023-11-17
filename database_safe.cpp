#pragma once
#include <msclr/gcroot.h>
#include <string>
#include "utils.cpp"

namespace angarawindows {

	//Мне самому стыдно за этот код
	//я не нашёл способа передать ссылку на функции reader->FUNCTION

	using namespace System;
	using namespace System::Data::OleDb;

	int getInt(msclr::gcroot <OleDbDataReader^> reader, String^ name, int def) {
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return def;
		
		return reader->GetInt32(id);
	}
	
	int getInt(msclr::gcroot <OleDbDataReader^> reader, String^ name) {
		return getInt(reader, name, 0);
	}


	short getShort(msclr::gcroot <OleDbDataReader^> reader, String^ name, short def) {
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return def;
		
		return reader->GetInt16(id);
	}
	
	short getShort(msclr::gcroot <OleDbDataReader^> reader, String^ name) {
		return getShort(reader, name, 0);
	}


	long long getLongLong(msclr::gcroot <OleDbDataReader^> reader, String^ name, long long def) {
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return def;
		
		return reader->GetInt64(id);
	}
	
	long long getLongLong(msclr::gcroot <OleDbDataReader^> reader, String^ name) {
		return getLongLong(reader, name, 0);
	}


	double getDouble(msclr::gcroot <OleDbDataReader^> reader, String^ name, double def) {
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return def;
		
		return reader->GetDouble(id);
	}
	
	double getDouble(msclr::gcroot <OleDbDataReader^> reader, String^ name) {
		return getDouble(reader, name, 0);
	}


	float getFloat(msclr::gcroot <OleDbDataReader^> reader, String^ name, float def) {
		int id = reader->GetOrdinal(name);

		if (reader->IsDBNull(id))
			return def;
		
		return reader->GetFloat(id);
	}
	
	float getFloat(msclr::gcroot <OleDbDataReader^> reader, String^ name) {
		return getFloat(reader, name, 0);
	}

	std::string getString(msclr::gcroot <OleDbDataReader^> reader, String^ name, const char* def) {
		int id = reader->GetOrdinal(name);


		if (reader->IsDBNull(id))
			return std::string(def);
	
		return SysToStd(reader->GetString(id));
	}
	
	std::string getString(msclr::gcroot <OleDbDataReader^> reader, String^ name) {
		return getString(reader, name, 0);
	}
}