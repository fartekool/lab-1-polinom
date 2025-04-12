#pragma once
#include <string>
#include <msclr\marshal_cppstd.h>
#include "../polynom/polynom.h"
#include "../polynom/polynom.cpp"
#include "../polynomial_algebra/expression.h"
#include "../polynomial_algebra/ExpressionValidator.h"
#include "../polynomial_algebra/InfixToPostfixConverter.h"
#include "../polynomial_algebra/Parser.h"
#include "../polynomial_algebra/PostfixCalculator.h"
#include "../polynomial_algebra/stack.h"

#include "../polynomial_algebra/expression.cpp"
#include "../polynomial_algebra/ExpressionValidator.cpp"
#include "../polynomial_algebra/InfixToPostfixConverter.cpp"
#include "../polynomial_algebra/Parser.cpp"
#include "../polynomial_algebra/PostfixCalculator.cpp"
#include "../polynomial_algebra/stack.h"

#include "../tables/tables_manager.h"
namespace graphicalinterface {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	Tables_manager<string, Polynom> table;
	TableType cur_type = TableType::ARRAY_TABLE;
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{	
			InitializeComponent();
			this->BackColor = Color::FromArgb(255, 255, 255);
			this->Width = 1600;
			this->Height = 900;
			this->StartPosition = FormStartPosition::CenterScreen;
			this->BackgroundImage = Image::FromFile("../graphical_interface/image.jpg");
			
			textBox1->Enter += gcnew System::EventHandler(this, &MyForm::textBox1_Enter);
			textBox1->Leave += gcnew System::EventHandler(this, &MyForm::textBox1_Leave);

			textBox2->Enter += gcnew System::EventHandler(this, &MyForm::textBox2_Enter);
			textBox2->Leave += gcnew System::EventHandler(this, &MyForm::textBox2_Leave);

			textBox3->Enter += gcnew System::EventHandler(this, &MyForm::textBox3_Enter);
			textBox3->Leave += gcnew System::EventHandler(this, &MyForm::textBox3_Leave);

			textBox4->Enter += gcnew System::EventHandler(this, &MyForm::textBox4_Enter);
			textBox4->Leave += gcnew System::EventHandler(this, &MyForm::textBox4_Leave);

			SetupGridView();
		}
	private:
		System::Void UpdateGrid()
		{
			polynomialGridView->Rows->Clear();

			for (auto& item : table.GetAllRecords())
			{
				polynomialGridView->Rows->Add(gcnew String(item.key.c_str()), gcnew String(item.data.GetInfix().c_str()));
			}
		}
	private: 
		System::Void SetupGridView()
		{	
			DataGridViewButtonColumn^ derivativeColumn = gcnew DataGridViewButtonColumn();
			derivativeColumn->HeaderText = "Производная";
			derivativeColumn->Text = "Взять";
			derivativeColumn->UseColumnTextForButtonValue = true;

			DataGridViewButtonColumn^ integralColumn = gcnew DataGridViewButtonColumn();
			integralColumn->HeaderText = "Интеграл";
			integralColumn->Text = "Взять";
			integralColumn->UseColumnTextForButtonValue = true;

			DataGridViewButtonColumn^ deleteColumn = gcnew DataGridViewButtonColumn();
			deleteColumn->HeaderText = "Удалить";
			deleteColumn->Text = "X";
			deleteColumn->UseColumnTextForButtonValue = true;

			polynomialGridView->Columns->Add("Name", "Имя");
			polynomialGridView->Columns->Add("Polynom", "Полином");
			polynomialGridView->Columns->Add(derivativeColumn);
			polynomialGridView->Columns->Add(integralColumn);
			polynomialGridView->Columns->Add(deleteColumn);

			polynomialGridView->CellMouseEnter += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::polynomialGridView_CellMouseEnter);
			polynomialGridView->CellMouseLeave += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::polynomialGridView_CellMouseLeave);

		}
	private: System::Void polynomialGridView_CellMouseEnter(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		if (e->RowIndex >= 0 && e->ColumnIndex == 4) {
			polynomialGridView->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->BackColor = System::Drawing::Color::Red;
			polynomialGridView->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->ForeColor = System::Drawing::Color::White;
			polynomialGridView->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->Font =
				gcnew System::Drawing::Font(polynomialGridView->Font, System::Drawing::FontStyle::Bold);
		}
	}
	private: System::Void polynomialGridView_CellMouseLeave(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		if (e->RowIndex >= 0 && e->ColumnIndex == 4) {
			polynomialGridView->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->BackColor = System::Drawing::Color::White;
			polynomialGridView->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->ForeColor = System::Drawing::Color::Red;
		}
	}
	private: System::Void textBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (textBox1->Text == "Имя") {
			textBox1->Text = "";
			textBox1->ForeColor = System::Drawing::Color::Black;
		}
	}

	private: System::Void textBox1_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (textBox1->Text == "") {
			textBox1->Text = "Имя";
			textBox1->ForeColor = System::Drawing::Color::Gray;
		}
	}
	private: System::Void textBox2_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (textBox2->Text == "Полином") {
			textBox2->Text = "";
			textBox2->ForeColor = System::Drawing::Color::Black;
		}
	}

	private: System::Void textBox2_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (textBox2->Text == "") {
			textBox2->Text = "Полином";
			textBox2->ForeColor = System::Drawing::Color::Gray;
		}
	}
	private: System::Void textBox3_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (textBox3->Text == "Имя") {
			textBox3->Text = "";
			textBox3->ForeColor = System::Drawing::Color::Black;
		}
	}
	private: System::Void textBox3_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (textBox3->Text == "") {
			textBox3->Text = "Имя";
			textBox3->ForeColor = System::Drawing::Color::Gray;
		}
	}
	private: System::Void textBox4_Enter(System::Object^ sender, System::EventArgs^ e) {
		if (textBox4->Text == "Выражение") {
			textBox4->Text = "";
			textBox4->ForeColor = System::Drawing::Color::Black;
		}
	}

	private: System::Void textBox4_Leave(System::Object^ sender, System::EventArgs^ e) {
		if (textBox4->Text == "") {
			textBox4->Text = "Выражение";
			textBox4->ForeColor = System::Drawing::Color::Gray;
		}
	}
		ref struct InputDialogResult {
			System::String^ name;
			char variable;
		};
		InputDialogResult^ ShowInputDialog(bool flag, String^ name) // 0 - der, 1 - int
		{
			System::Windows::Forms::Form^ form = gcnew System::Windows::Forms::Form();
			System::Windows::Forms::Label^ label = gcnew System::Windows::Forms::Label();
			System::Windows::Forms::TextBox^ textBox = gcnew System::Windows::Forms::TextBox();
			System::Windows::Forms::RadioButton^ radioX = gcnew System::Windows::Forms::RadioButton();
			System::Windows::Forms::RadioButton^ radioY = gcnew System::Windows::Forms::RadioButton();
			System::Windows::Forms::RadioButton^ radioZ = gcnew System::Windows::Forms::RadioButton();
			System::Windows::Forms::Button^ buttonOk = gcnew System::Windows::Forms::Button();
			System::Windows::Forms::Button^ buttonCancel = gcnew System::Windows::Forms::Button();

			if (flag)
				form->Text = "Создание интеграла";
			else
				form->Text = "Создание производной";

			label->Text = "Введите имя нового полинома:";
			textBox->Text = name;

			radioX->Text = "x";
			radioY->Text = "y";
			radioZ->Text = "z";
			radioX->Checked = true;  // По умолчанию выбрана x

			buttonOk->Text = "OK";
			buttonCancel->Text = "Отмена";

			buttonOk->DialogResult = System::Windows::Forms::DialogResult::OK;
			buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;

			// Расположение элементов
			label->SetBounds(10, 10, 300, 20);
			textBox->SetBounds(10, 40, 300, 20);
			radioX->SetBounds(10, 70, 50, 20);
			radioY->SetBounds(70, 70, 50, 20);
			radioZ->SetBounds(130, 70, 50, 20);
			buttonOk->SetBounds(50, 100, 75, 25);
			buttonCancel->SetBounds(150, 100, 75, 25);

			form->ClientSize = System::Drawing::Size(320, 140);
			form->Controls->AddRange(gcnew cli::array<System::Windows::Forms::Control^>{ label, textBox, radioX, radioY, radioZ, buttonOk, buttonCancel });
			form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			form->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			form->AcceptButton = buttonOk;
			form->CancelButton = buttonCancel;

			if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				InputDialogResult^ result = gcnew InputDialogResult();
				result->name = textBox->Text;

				if (radioX->Checked) result->variable = 'x';
				else if (radioY->Checked) result->variable = 'y';
				else result->variable = 'z';

				return result;
			}

			return nullptr;
		}
	private:
		System::Void polynomialGridView_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
		{	
			if (e->RowIndex < 0)
				return;
			if (e->ColumnIndex == 2 || e->ColumnIndex == 3) // Производная и интеграл
			{	
				InputDialogResult^ result;
				if (e->ColumnIndex == 2)
					result = ShowInputDialog(false, polynomialGridView->Rows[e->RowIndex]->Cells[0]->Value->ToString());
				if (e->ColumnIndex == 3)
					result = ShowInputDialog(true, polynomialGridView->Rows[e->RowIndex]->Cells[0]->Value->ToString());
				if (result != nullptr && !String::IsNullOrWhiteSpace(result->name))
				{
					std::string new_name = msclr::interop::marshal_as<std::string>(result->name->ToString());
					System::String^ polyName = polynomialGridView->Rows[e->RowIndex]->Cells[0]->Value->ToString();
					std::string cur_name = msclr::interop::marshal_as<std::string>(polyName);
					Polynom cur_pol = table.find(cur_name);

					Polynom new_pol;
					if (e->ColumnIndex == 2)
						new_pol = cur_pol.derivative(result->variable);
					if (e->ColumnIndex == 3)
						new_pol = cur_pol.integrate(result->variable);
					if (result->name == polyName)
					{
						table.find(cur_name) = new_pol;
						UpdateGrid();
					}
					else if (table.insert(new_name, new_pol))
						UpdateGrid();
					else
						MessageBox::Show("Ошибка", "Полином уже существует!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			
			if (e->ColumnIndex == 4) // Удаление
			{
				System::String^ polyName = polynomialGridView->Rows[e->RowIndex]->Cells[0]->Value->ToString();
				std::string name = msclr::interop::marshal_as<std::string>(polyName);

				System::Windows::Forms::DialogResult result = MessageBox::Show(
					"Удалить полином '" + polyName + "'?", "Подтверждение",
					MessageBoxButtons::YesNo, MessageBoxIcon::Warning);

				if (result == System::Windows::Forms::DialogResult::Yes)
				{
					
					table.delete_rec(name);
					UpdateGrid();
					

				}
			}
		}
	private:
		
	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;



	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::DataGridView^ polynomialGridView;
	private: System::Windows::Forms::ImageList^ imageList1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;










	private: System::ComponentModel::IContainer^ components;



	private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{	
			this->components = (gcnew System::ComponentModel::Container());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->polynomialGridView = (gcnew System::Windows::Forms::DataGridView());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->polynomialGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->ForeColor = System::Drawing::Color::Gray;
			this->textBox1->Location = System::Drawing::Point(137, 81);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(366, 31);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"Имя";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->ForeColor = System::Drawing::Color::Gray;
			this->textBox2->Location = System::Drawing::Point(137, 155);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(366, 31);
			this->textBox2->TabIndex = 1;
			this->textBox2->Text = L"Полином";
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->ForeColor = System::Drawing::Color::Gray;
			this->textBox3->Location = System::Drawing::Point(2180, 81);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(366, 31);
			this->textBox3->TabIndex = 0;
			this->textBox3->Text = L"Имя";
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			// 
			// textBox4
			// 
			this->textBox4->ForeColor = System::Drawing::Color::Gray;
			this->textBox4->Location = System::Drawing::Point(2180, 155);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(366, 31);
			this->textBox4->TabIndex = 1;
			this->textBox4->Text = L"Выражение";
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox4_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(137, 345);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(366, 160);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Добавить\r\n";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(2180, 345);
			this->button4->Name = L"button1";
			this->button4->Size = System::Drawing::Size(366, 160);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Добавить\r\n";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// polynomialGridView
			// 
			this->polynomialGridView->AllowUserToAddRows = false;
			this->polynomialGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->polynomialGridView->Location = System::Drawing::Point(760, 81);
			this->polynomialGridView->Name = L"polynomialGridView";
			this->polynomialGridView->ReadOnly = true;
			this->polynomialGridView->RowHeadersWidth = 82;
			this->polynomialGridView->RowTemplate->Height = 33;
			this->polynomialGridView->Size = System::Drawing::Size(1163, 642);
			this->polynomialGridView->TabIndex = 4;
			this->polynomialGridView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::polynomialGridView_CellContentClick);
			// 
			// imageList1
			// 
			this->imageList1->ColorDepth = System::Windows::Forms::ColorDepth::Depth8Bit;
			this->imageList1->ImageSize = System::Drawing::Size(16, 16);
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(1760, 772);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(163, 68);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Удалить все";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(760, 772);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(196, 68);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Выбор Таблицы";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(2047, 1146);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->polynomialGridView);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox4);
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Text = L"Polynom";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->polynomialGridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ NAME = textBox1->Text;
		string name = msclr::interop::marshal_as<std::string>(NAME);
		if (!ValidateName(name))
		{
			MessageBox::Show("Ошибка", "Некорректное имя!", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		String^ POLYNOM_STR = textBox2->Text;
		string polynom_str = msclr::interop::marshal_as<std::string>(POLYNOM_STR);
		try
		{
			Polynom polynom(polynom_str);
			if (table.insert(name, polynom))
				UpdateGrid();
			else
			{
				MessageBox::Show("Ошибка", "Полином уже существует!", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		catch (const std::exception& e)
		{
			System::String^ errorMessage = gcnew System::String(e.what());
			MessageBox::Show("Ошибка: " + errorMessage, "Некорректный ввод полинома!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}


		/*try {
			

			try
			{
				Polynom polynom(exp);
				
				if (table.insert(name, polynom))
					UpdateGrid();
				else {
					MessageBox::Show("Ошибка", "Полином уже существует!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			catch (const std::exception& e)
			{	
				Expression exp1(exp);

				vector<string> poly_names = exp1.GetOperands();

				map<string, Polynom> pol;

				for (string& i : poly_names)
				{
					pol.insert(std::make_pair(i, table.find(i)));
				}

				Polynom result = exp1.Calculate(pol);


				if (table.insert(name, result))
					UpdateGrid();
				else {
					MessageBox::Show("Ошибка", "Полином уже существует!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}
		catch (const std::exception& e)
		{
			System::String^ errorMessage = gcnew System::String(e.what());
			MessageBox::Show("Ошибка: " + errorMessage, "Некорректный ввод полинома!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}*/


	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ NAME = textBox3->Text;
		string name = msclr::interop::marshal_as<std::string>(NAME);
		if (!ValidateName(name))
		{
			MessageBox::Show("Ошибка", "Некорректное имя!", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		String^ EXPRESSION_STR = textBox4->Text;
		string expression_str = msclr::interop::marshal_as<std::string>(EXPRESSION_STR);

		try
		{
			Expression exp(expression_str);
			vector<string> poly_names = exp.GetOperands();

			map<string, Polynom> pol;

			for (string& i : poly_names)
			{
				pol.insert(std::make_pair(i, table.find(i)));
			}
			Polynom result = exp.Calculate(pol);

			if (table.insert(name, result))
				UpdateGrid();
			else {
				MessageBox::Show("Ошибка", "Полином уже существует!", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		catch (const std::exception& e)
		{
			System::String^ errorMessage = gcnew System::String(e.what());
			MessageBox::Show("Ошибка: " + errorMessage, "Некорректный ввод выражения!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e){
		
		if (e->KeyCode == Keys::Enter) {
			button1->PerformClick(); 
			e->SuppressKeyPress = true;
		}
		if (e->KeyCode == Keys::Up)
			MyForm::ActiveControl = textBox1;
		if (e->KeyCode == Keys::Down)
			MyForm::ActiveControl = textBox2;
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {

		if (table.GetFill() == 0)
			System::Windows::Forms::DialogResult result = MessageBox::Show("Таблица пустая!", "Ошибка");
		else
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"Удалить все полиномы?", "Подтверждение",
				MessageBoxButtons::YesNo, MessageBoxIcon::Warning);

			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				table = Tables_manager<string, Polynom>();
				table.set_current(cur_type);
				polynomialGridView->Rows->Clear();
			}
		}

	}
	
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {

		System::Windows::Forms::Form^ form = gcnew System::Windows::Forms::Form();
		System::Windows::Forms::Label^ label = gcnew System::Windows::Forms::Label();

		System::Windows::Forms::RadioButton^ radio_ARRAY_TABLE = gcnew System::Windows::Forms::RadioButton();
		System::Windows::Forms::RadioButton^ radio_AVL_TREE_TABLE = gcnew System::Windows::Forms::RadioButton();
		System::Windows::Forms::RadioButton^ radio_HASH_CHAINING_TABLE = gcnew System::Windows::Forms::RadioButton();
		System::Windows::Forms::RadioButton^ radio_HASH_OPEN_ADDR_TABLE = gcnew System::Windows::Forms::RadioButton();
		System::Windows::Forms::RadioButton^ radio_LIST_TABLE = gcnew System::Windows::Forms::RadioButton();
		System::Windows::Forms::RadioButton^ radio_SORTED_ARRAY_TABLE = gcnew System::Windows::Forms::RadioButton();

		System::Windows::Forms::Button^ buttonOk = gcnew System::Windows::Forms::Button();
		System::Windows::Forms::Button^ buttonCancel = gcnew System::Windows::Forms::Button();
		form->Text = "Выбор таблицы";
		label->Text = "Выберите таблицу:";

		radio_ARRAY_TABLE->Text = "Array Table";
		radio_AVL_TREE_TABLE->Text = "AVL Tree Table";
		radio_HASH_CHAINING_TABLE->Text = "Hash Chaining Table";
		radio_HASH_OPEN_ADDR_TABLE->Text = "Hash Open Addr Table";
		radio_LIST_TABLE->Text = "List Table";
		radio_SORTED_ARRAY_TABLE->Text = "Sorted Array Table";
		if (cur_type == TableType::ARRAY_TABLE)
			radio_ARRAY_TABLE->Checked = true;
		else if (cur_type == TableType::AVL_TREE_TABLE)
			radio_AVL_TREE_TABLE->Checked = true;
		else if (cur_type == TableType::HASH_CHAINING_TABLE)
			radio_HASH_CHAINING_TABLE->Checked = true;
		else if (cur_type == TableType::HASH_OPEN_ADDR_TABLE)
			radio_HASH_OPEN_ADDR_TABLE->Checked = true;
		else if (cur_type == TableType::LIST_TABLE)
			radio_LIST_TABLE->Checked = true;
		else if (cur_type == TableType::SORTED_ARRAY_TABLE)
			radio_SORTED_ARRAY_TABLE->Checked = true;

		buttonOk->Text = "OK";
		buttonCancel->Text = "Отмена";

		buttonOk->DialogResult = System::Windows::Forms::DialogResult::OK;
		buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;

		label->SetBounds(10, 10, 300, 20);

		radio_ARRAY_TABLE->SetBounds(10, 70, 200, 20);
		radio_AVL_TREE_TABLE->SetBounds(10, 120, 200, 20);
		radio_HASH_CHAINING_TABLE->SetBounds(10, 170, 200, 20);
		radio_HASH_OPEN_ADDR_TABLE->SetBounds(10, 220, 200, 20);
		radio_LIST_TABLE->SetBounds(10, 270, 200, 20);
		radio_SORTED_ARRAY_TABLE->SetBounds(10, 320, 200, 20);


		buttonOk->SetBounds(50, 350, 75, 25);
		buttonCancel->SetBounds(150, 350, 75, 25);

		form->ClientSize = System::Drawing::Size(300, 400);
		form->Controls->AddRange(gcnew cli::array<System::Windows::Forms::Control^>{ label, radio_ARRAY_TABLE, radio_AVL_TREE_TABLE, radio_HASH_CHAINING_TABLE, radio_HASH_OPEN_ADDR_TABLE, radio_LIST_TABLE, radio_SORTED_ARRAY_TABLE, buttonOk, buttonCancel });
		form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		form->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		form->AcceptButton = buttonOk;
		form->CancelButton = buttonCancel;

		if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if (radio_ARRAY_TABLE->Checked)
				cur_type = TableType::ARRAY_TABLE;
			else if (radio_AVL_TREE_TABLE->Checked)
				cur_type = TableType::AVL_TREE_TABLE;
			else if (radio_HASH_CHAINING_TABLE->Checked)
				cur_type = TableType::HASH_CHAINING_TABLE;
			else if (radio_HASH_OPEN_ADDR_TABLE->Checked)
				cur_type = TableType::HASH_OPEN_ADDR_TABLE;
			else if (radio_LIST_TABLE->Checked)
				cur_type = TableType::LIST_TABLE;
			else if (radio_SORTED_ARRAY_TABLE->Checked)
				cur_type = TableType::SORTED_ARRAY_TABLE;

			table.set_current(cur_type);
			UpdateGrid();
		}
	}
	
	};
}
