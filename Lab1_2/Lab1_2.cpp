
#include "Lab1_2.h"


const char* msgs[] = { "0. �����",
"1. ������ ����� ���������� �������",
"2. ������ ����� ������� ����",
"3. ������� �������� ������ ����� �� �������� ��������",
"4. ������� ����� ���� ������ ����� �� �� �������� �� ��� �������",
"5. ������� ������ �������� ������ ����� ������������ ���������� �� ��� �������",
"6. ������� ���������� ������ �������� ������ ����� � ���������� ������� ��������� ������������ ���������� �� ��� �������",
"7. ������� ������� ������������� ��������, ������������ ������ ������ � �� ��������� �� ��� ������� (����� �������� = �������� ������� ������)" };

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);


namespace Lab1_2 {

	// ����� ������ ������������
	int dialog(const char* msgs[], int N) {
		const char* errmsgs = "";
		int rc, i;
		do {
			puts(errmsgs);
			errmsgs = "������! ��������� ����!";
			for (i = 0; i < N; ++i)					// ����� ������ �����������
				puts(msgs[i]);
			printf("��������: --> ");
		} while (getNum(rc) < 0 || rc >= N);
		return rc;
	}


	// "1. ������ ����� ���������� �������"
	int D_SetPoint(Class::Catenary& C) {


		return 1;
	}

	// "2. ������ ����� ������� ����"
	int D_SetBorders(Class::Catenary& C) {


		return 1;
	}

	// "3. ������� �������� ������ ����� �� �������� ��������",
	int D_GetOrdinate(Class::Catenary& C) {


		return 1;
	}

	// "4. ������� ����� ���� ������ ����� �� �� �������� �� ��� �������"
	int D_GetLength(Class::Catenary& C) {


		return 1;
	}

	// "5. ������� ������ �������� ������ ����� ������������ ���������� �� ��� �������"
	int D_GetRadius(Class::Catenary& C) {


		return 1;
	}

	// "6. ������� ���������� ������ �������� ������ ����� � ���������� ������� ��������� ������������ ���������� �� ��� �������"
	int D_GetCenter(Class::Catenary& C) {


		return 1;
	}

	//"7. ������� ������� ������������� ��������, ������������ ������ ������ � �� ��������� �� ��� ������� (����� �������� = �������� ������� ������)"
	int D_GetArea(Class::Catenary&) {


		return 1;
	}

}

