#include <iostream>
#include <Windows.h>
#include <exception>
#include <string>

class MyFile {
public:
	MyFile(const char* file_name, DWORD access, DWORD disposition) : f_access(access) {
		// convert to wchar
		unsigned int name_num = MultiByteToWideChar(CP_UTF8, 0, file_name, -1, NULL, 0);
		this->f_name = new wchar_t[name_num];
		MultiByteToWideChar(CP_UTF8, 0, file_name, -1, this->f_name, name_num);

		this->hfile = CreateFile(
			this->f_name,
			this->f_access,
			0,
			NULL,
			disposition,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (this->hfile == INVALID_HANDLE_VALUE) {
			CloseHandle(this->hfile);
			throw std::exception("Couldn't create/open file");
		}
	}

	~MyFile() {
		CloseHandle(this->hfile);
		delete[] this->f_name;
	}

	template <typename T>
	MyFile& operator>> (T& value);
	
	template <typename T>
	MyFile& operator<< (T& value);
	
private:
	TCHAR* f_name;
	DWORD f_access;
	HANDLE hfile;
};


template <typename T>
MyFile& MyFile::operator>> (T& value) {
	if (!(this->f_access & GENERIC_READ))
		throw std::exception("Don't support read operation");
	
	bool is_correct_read = false;
	unsigned long count = 0;

	if (this->hfile == INVALID_HANDLE_VALUE) {
		CloseHandle(this->hfile);
		throw std::exception("Error operation");
	}

	is_correct_read = ReadFile(this->hfile, &value, sizeof(T), &count, NULL);

	if (!is_correct_read || sizeof(T) != count) {
		CloseHandle(this->hfile);
		throw std::exception("Couldn't do your operation");
	}

	SetFilePointer(this->hfile, 0, NULL, FILE_BEGIN);

	return *this;
}

template <typename T>
MyFile& MyFile::operator<< (T& value) {
	if (!(this->f_access & GENERIC_WRITE))
		throw std::exception("Don't support write operation");

	bool is_correct_write = false;
	unsigned long count = 0;

	if (this->hfile == INVALID_HANDLE_VALUE) {
		CloseHandle(this->hfile);
		throw std::exception("Error operation");
	}

	is_correct_write = WriteFile(this->hfile, &value, sizeof(T), &count, NULL);

	if (!is_correct_write || sizeof(T) != count) {
		CloseHandle(this->hfile);
		throw std::exception("Couldn't do your operation");
	}

	SetFilePointer(this->hfile, 0, NULL, FILE_BEGIN);

	return *this;
}

//#define TEST_1
#define TEST_2

int main() {
	try {
#ifdef TEST_1
		MyFile file1("my_file1.dat", GENERIC_WRITE, CREATE_NEW);
#endif
#ifdef TEST_2
		MyFile file2("my_file2.dat", GENERIC_READ | GENERIC_WRITE, OPEN_ALWAYS);
#endif
		//============================================
#ifdef TEST_1
		const char str1[] = "hello\n";
		char str2[] = "world\n";

		file1 << str1;
		file1 << str2;
		file1 << "!!!\n";

		char a;
		file1 >> a; // can't have rigth
#endif
		//============================================
#ifdef TEST_2
		int a = 5;
		file2 << a;

		a = 0;
		file2 >> a;

		char c = 'r';
		file2 << c;

		c = ' ';
		file2 >> c;

		std::string s = "hello";
		file2 << s;

		s = "";
		file2 >> s;
#endif
	}
	catch (const std::exception msg) {
		// convert msg
		unsigned int wchars_num = MultiByteToWideChar(CP_UTF8, 0, msg.what(), -1, NULL, 0);
		wchar_t* wstr = new wchar_t[wchars_num];
		MultiByteToWideChar(CP_UTF8, 0, msg.what(), -1, wstr, wchars_num);

		MessageBox(0, wstr, L"Error", 0);

		delete[] wstr;
	}

	return 0;
}
