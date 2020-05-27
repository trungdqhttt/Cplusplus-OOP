#include "CDate.h"

const int CDate::MonthsInYear[13] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
const int CDate::DaysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

CDate CDate::operator + (int days) {	
	CDate res;
	int nMaxDays = DaysInMonth[month] + (month == 2 && isLeapYear(year) ? 1 : 0);

	int nYear = year;
	int nMonth = month;
	int nDays = day + days;

	while (nDays > nMaxDays) {
		nDays -= nMaxDays;

		++nMonth;

		if (nMonth > 12) {
			nMonth = 1; 
			++nYear;  
		}
		nMaxDays = DaysInMonth[nMonth] + (nMonth == 2 && isLeapYear(nYear) ? 1 : 0);
	}
	res.setDate(nDays, nMonth, nYear);
	return res;
}

CDate CDate::operator - (int days) {
	CDate res;
	if ((day - days) > 0) {
		res.setDate(day - days, month, year);
		return res;
	}

	int nYear = year;
	int nDays = days; 
	nDays -= day; // Bắt đầu thực hiện từ ngày sau khi - đi days trở về ngày đầu của tháng

	// Kiểm tra xem TH có rơi vào năm trước không
	int nMonth = month - 1;
	if (nMonth < 1) {
		nMonth = 12;
		--nYear;
	}

	int nDaysInMonth = DaysInMonth[nMonth] + (nMonth == 2 && isLeapYear(nYear) ? 1 : 0);

	while (nDays >= 0) {
		nDays -= nDaysInMonth;

		// Kiểm tra xem TH rơi vào tháng trước
		if (nDays > 0) {
			--nMonth;

			// Kiểm tra xem TH có rơi vào năm trước không
			if (nMonth < 1) {
				nMonth = 12;
				--nYear; 
			}
		}
		// Cập nhật số ngày của tháng mới
		nDaysInMonth = DaysInMonth[nMonth] + (nMonth == 2 && isLeapYear(nYear) ? 1 : 0);
	}

	res.setDate((nDays > 0 ? nDays : -nDays), nMonth, nYear);
	return res;
}

CDate CDate::operator ++ () {
	int tmp = DaysInMonth[month] + (month == 2 && isLeapYear(year) ? 1 : 0);
	if (day < tmp) {
		day++;
	}
	else if (month != 12) {
		day = 1;
		month++;
	}
	else {
		day = month = 1;
		year++;
	}
	return *this;
}

CDate CDate::operator ++ (int val) {
	CDate tmp = *this;
	int dayTmp = DaysInMonth[month] + (month == 2 && isLeapYear(year) ? 1 : 0);
	if (day < dayTmp) {
		day++;
	}
	else if (month != 12) {
		day = 1;
		month++;
	}
	else {
		day = month = 1;
		year++;
	}
	return tmp;
}

CDate CDate::operator -- () {
	if ((day - 1) > 0) {
		--day;
		return *this;
	}

	int nDays = 1 - day;

	int nMonth = month - 1;
	if (nMonth < 1) {
		nMonth = 12;
		--year;
	}

	int nDayInMonth = DaysInMonth[nMonth] + (nMonth == 2 && isLeapYear(year) ? 1 : 0);

	if (nDays == 0) {
		nDays -= nDayInMonth;

		if (nDays > 0) {
			--nMonth;

			if (nMonth < 1) {
				nMonth = 12;
				--year;
			}
		}
	}

	day = (nDays > 0 ? nDays : -nDays);
	return *this;
}

CDate CDate::operator -- (int day) {
	CDate tmp = *this;

	if ((day - 1) > 0) {
		day--;
		return tmp;
	}

	int nDays = 1 - day;

	int nMonth = month - 1;
	if (nMonth < 1) {
		nMonth = 12;
		--year;
	}

	int nDaysInMonth = DaysInMonth[nMonth] + (nMonth == 2 && isLeapYear(year) ? 1 : 0);

	if (nDays == 0) {
		nDays -= nDaysInMonth;

		if (nDays > 0) {
			--nMonth;

			if (nMonth < 1) {
				nMonth = 12;
				--year;
			}
		}
	}

	day = nDays > 0 ? nDays : -nDays;
	return tmp;
}

int CDate::countLeapYears() {
	if (month <= 2) {
		year--;
	}

	return year / 4 - year / 100 + year / 400;
}

int CDate::operator -(CDate d) {
	long int n1 = year * 365 + day;

	for (int i = 1; i < month; i++) {
		n1 += DaysInMonth[i];
	}
	n1 += countLeapYears();

	long int n2 = d.year * 365 + d.day;
	for (int i = 1; i < d.month; i++) {
		n2 += DaysInMonth[i];
	}
	n2 += d.countLeapYears();

	return (n2 - n1);
}

void Menu(CDate d1, CDate d2) {
	while (true) {
		system("cls");
		cout << "\n\n\t\t ===================== OOP-CDate =====================\n";
		cout << "\n\t 1. Nhap ngay.";
		cout << "\n\t 2. Xuat ngay da nhap.";
		cout << "\n\t 3. Cong mot gia tri ngay bat ky.";
		cout << "\n\t 4. Tru mot gia tri ngay bat ky.";
		cout << "\n\t 5. Ngay tiep theo.";
		cout << "\n\t 6. Ngay truoc do.";
		cout << "\n\t 7. Khoang cach giua hai ngay.";
		cout << "\n\t 0. Thoat chuong trinh.";

		int query;
		do {
			cout << "\n\n Nhap lua chon cua ban: ";
			cin >> query;
			if (query < 0 || query > 7) {
				cout << "\n Lua chon khong hop le!\n";
			}
		} while (query < 0 || query > 7);

		switch (query) {
		case 1:
			system("cls");
			cout << "\n\n\t\t ============ NHAP THONG TIN NGAY ============\n";
			cout << "\n Nhap thong tin ngay thu nhat: ";
			cin >> d1;
			cout << "\n Nhap thong tin ngay thu hai: ";
			cin >> d2;
			break;
		case 2:
			system("cls");
			cout << "\n\n\t\t ============ THONG TIN NGAY DA NHAP ============\n";
			cout << "\n\t Ngay thu nhat: " << d1 << endl;
			cout << "\n\t Ngay thu hai: " << d2 << "\n\n";
			system("pause");
			break;
		case 3:
		{
			system("cls");
			int days;
			cout << "\n Nhap so ngay muon cong: ";
			cin >> days;
			cout << "\n\t Ngay thu nhat (" << d1 << ") sau khi + " << days << " ngay: " 
				<< d1 + days << endl;
			cout << "\n\t Ngay thu hai (" << d2 << ") sau khi + " << days << " ngay: " 
				<< d2 + days << "\n\n";
			system("pause");
		}
			break;
		case 4:
		{
			system("cls");
			int days;
			cout << "\n Nhap so ngay muon tru: ";
			cin >> days;
			cout << "\n\t Ngay thu nhat (" << d1 << ") sau khi - " << days << " ngay: "
				<< d1 - days << endl;
			cout << "\n\t Ngay thu hai (" << d2 << ") sau khi - " << days << " ngay: " 
				<< d2 - days << "\n\n";
			system("pause");
		}
			break;
		case 5:
		{
			system("cls");
			// Bản chất của toán tử ++ là thay đổi trực tiếp vào d1 hoặc d2 nên ta dùng biến tmp để xử lý nhắm không bị thay đổi d1, d2
			CDate tmp1 = d1;
			CDate tmp2 = d2;
			cout << "\n\t Ngay tiep theo cua ngay " << d1 << " la: " << ++tmp1 << endl;
			cout << "\n\t Ngay tiep theo cua ngay " << d2 << " la: " << ++tmp2 << "\n\n";
			system("pause");
		}
			break;
		case 6:
		{
			system("cls");
			// Tương tự như toán tử ++
			CDate tmp1 = d1;
			CDate tmp2 = d2;
			cout << "\n\t Ngay truoc do cua ngay " << d1 << " la: " << --tmp1 << endl;
			cout << "\n\t Ngay truoc do cua ngay " << d2 << " la: " << --tmp2 << "\n\n";
			system("pause");
		}
			break;
		case 7:
		{
			system("cls");
			CDate tmp;
			cout << "\n\t Khoang cach tu ngay " << d1 << " den ngay " << d2 << " la: "
				<< d1 - d2 << " ngay\n\n";
			system("pause");
		}
		case 0:
			cout << "\n\t =========== THE END ===========\n";
			return;
		}

	}
}

ostream& operator << (ostream& os, const CDate d) {
	os << setw(2) << setfill('0') << d.day << "/";
	os << setw(2) << setfill('0') << d.month << "/";
	os << d.year;
	return os;
}

istream& operator >> (istream& is, CDate& d) {
	bool kt;
	
	do {
		kt = true;
		cout << "\n Nhap ngay: ";
		is >> d.day;
		cout << "\n Nhap thang: ";
		is >> d.month;
		cout << "\n Nhap nam (>1900): ";
		is >> d.year;

		if ((d.month < 1) || (d.month > 12) || d.year < 1900) {
			cout << "\n Ngay khong hop le!";
			cout << "\n Vui long kiem tra lai.\n";
			kt = false;
		}
		else {
			bool isLeapYear = (d.year % 100) ? (d.year % 4 == 0) : (d.year % 400 == 0);
			if (d.day == 29 && d.month == 2 && isLeapYear) {
				d.day = 29;
			}
			else {
				if (!((d.day >= 1) && (d.day <= d.DaysInMonth[d.month]))) {
					cout << "\n Ngay khong hop le!";
					cout << "\n Vui long kiem tra lai.\n";
					kt = false;
				}
			}
		}
	} while (!kt);
	return is;
}
