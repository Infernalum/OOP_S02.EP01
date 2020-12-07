#ifndef AMMOBOX_H
#define AMMO_BOX


namespace XCom {

	class AmmoBox : public Item {
	private:

		int qty;				// ������� ���-�� �������� � �����;
		int maxQty;				// ����� ���-�� �������� � �����;
		double weightOfOne;		// ��� ������ �������


	protected:


	public:

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		// �����������, ��������� ������ ���� � 40 ��������� � �������� 2 TP �� �����������
		AmmoBox(int up = 2, double wof = 0.02, int maxqty = 40);

		// copy- move- ������������ �� ���������

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		int get_qty() { return qty; };
		int get_max_qty() { return maxQty; };
		double get_weight_of_one() { return weightOfOne; };


		/********************************************************/
		/*						�������							*/
		/********************************************************/

		// �������� ���� ����� � ���������
		virtual const AmmoBox& set_weight() override;

		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/


	};

}
#endif // !AMMOBOX_H


