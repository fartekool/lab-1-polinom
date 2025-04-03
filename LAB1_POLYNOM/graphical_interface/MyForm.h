#pragma once
#include <string>
#include <msclr\marshal_cppstd.h>
#include "../polynom/polynom.h"
#include "../polynom/polynom.cpp"
#include "../polynomial_algebra/expression.h"
#include "../tables/tables_manager.h"

namespace graphicalinterface {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	Tables_manager<string, Polynom> table;
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{	
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->BackColor = Color::FromArgb(255, 255, 255);
			this->Width = 1600;
			this->Height = 900;
			this->StartPosition = FormStartPosition::CenterScreen;
			this->BackgroundImage = Image::FromFile("../graphical_interface/image.jpg");

			textBox1->Enter += gcnew System::EventHandler(this, &MyForm::textBox1_Enter);
			textBox1->Leave += gcnew System::EventHandler(this, &MyForm::textBox1_Leave);

			textBox2->Enter += gcnew System::EventHandler(this, &MyForm::textBox2_Enter);
			textBox2->Leave += gcnew System::EventHandler(this, &MyForm::textBox2_Leave);

			SetupGridView();
			
			
		}
	private: 
		System::Void SetupGridView()
		{	
			DataGridViewButtonColumn^ derivativeColumn = gcnew DataGridViewButtonColumn();
			derivativeColumn->HeaderText = "Производная";

			DataGridViewButtonColumn^ integralColumn = gcnew DataGridViewButtonColumn();
			integralColumn->HeaderText = "Интеграл";

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
		//System::Void UpdateTable()
		//{
		//	polynomialGridView->Rows->Clear(); // Очистка таблицы

		//	for (const auto& record : arr_table.GetAll())
		//	{
		//		int rowIndex = polynomialGridView->Rows->Add();
		//		polynomialGridView->Rows[rowIndex]->Cells[0]->Value = gcnew System::String(record.key.c_str());
		//		polynomialGridView->Rows[rowIndex]->Cells[1]->Value = gcnew System::String(record.data.GetInfix().c_str());
		//	}
		//}
		/*System::String^ ShowInputDialog(System::String^ prompt, System::String^ title)
		{
			System::Windows::Forms::Form^ form = gcnew System::Windows::Forms::Form();
			System::Windows::Forms::Label^ label = gcnew System::Windows::Forms::Label();
			System::Windows::Forms::TextBox^ textBox = gcnew System::Windows::Forms::TextBox();
			System::Windows::Forms::Button^ buttonOk = gcnew System::Windows::Forms::Button();
			System::Windows::Forms::Button^ buttonCancel = gcnew System::Windows::Forms::Button();

			form->Text = title;
			label->Text = prompt;
			textBox->Text = "";

			buttonOk->Text = "OK";
			buttonCancel->Text = "Отмена";

			buttonOk->DialogResult = System::Windows::Forms::DialogResult::OK;
			buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;

			label->SetBounds(10, 10, 300, 20);
			textBox->SetBounds(10, 40, 300, 20);
			buttonOk->SetBounds(50, 70, 75, 25);
			buttonCancel->SetBounds(150, 70, 75, 25);

			form->ClientSize = System::Drawing::Size(320, 120);
			form->Controls->AddRange(gcnew cli::array<System::Windows::Forms::Control^>{ label, textBox, buttonOk, buttonCancel });
			form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			form->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			form->AcceptButton = buttonOk;
			form->CancelButton = buttonCancel;

			return (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) ? textBox->Text : nullptr;
		}*/
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

						table.delete_rec(cur_name);
						table.insert(cur_name, new_pol);
						polynomialGridView->Rows[e->RowIndex]->Cells[1]->Value = gcnew System::String(new_pol.GetInfix().c_str());
					}
					else if(table.insert(new_name, new_pol))
						polynomialGridView->Rows->Add(gcnew String(result->name), gcnew String(new_pol.GetInfix().c_str()));
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
					// Удаляем полином из таблицы
					table.delete_rec(name);
					//UpdateTable();  // Обновляем таблицу
					polynomialGridView->Rows->RemoveAt(e->RowIndex);

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

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ polynomialGridView;
	private: System::Windows::Forms::ImageList^ imageList1;








	private: System::ComponentModel::IContainer^ components;



	private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{	
			this->components = (gcnew System::ComponentModel::Container());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->polynomialGridView = (gcnew System::Windows::Forms::DataGridView());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
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
			// polynomialGridView
			// 
			this->polynomialGridView->AllowUserToAddRows = false;
			this->polynomialGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->polynomialGridView->Location = System::Drawing::Point(760, 81);
			this->polynomialGridView->Name = L"polynomialGridView";
			this->polynomialGridView->ReadOnly = true;
			this->polynomialGridView->RowHeadersWidth = 82;
			this->polynomialGridView->RowTemplate->Height = 33;
			this->polynomialGridView->Size = System::Drawing::Size(1214, 642);
			this->polynomialGridView->TabIndex = 4;
			this->polynomialGridView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::polynomialGridView_CellContentClick);
			// 
			// imageList1
			// 
			this->imageList1->ColorDepth = System::Windows::Forms::ColorDepth::Depth8Bit;
			this->imageList1->ImageSize = System::Drawing::Size(16, 16);
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(2047, 1146);
			this->Controls->Add(this->polynomialGridView);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
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
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		try {
			String^ NAME = textBox1->Text;
			String^ POLYNOM = textBox2->Text;
			std::string nameStr = msclr::interop::marshal_as<std::string>(textBox1->Text);
			std::string polynomStr = msclr::interop::marshal_as<std::string>(textBox2->Text);

			Polynom polynom(polynomStr);
			if (table.insert(nameStr, polynom))
				polynomialGridView->Rows->Add(gcnew String(NAME), gcnew String(POLYNOM));
			else {
				MessageBox::Show("Ошибка", "Полином уже существует!", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		catch (const std::exception& e)
		{
			System::String^ errorMessage = gcnew System::String(e.what());
			MessageBox::Show("Ошибка: " + errorMessage, "Некорректный ввод полинома!", MessageBoxButtons::OK, MessageBoxIcon::Error);
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

};
}
