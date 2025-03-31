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
			this->BackColor = Color::FromArgb(130, 171, 217);
			this->Width = 1600;
			this->Height = 900;
			this->StartPosition = FormStartPosition::CenterScreen;
			this->BackgroundImage = Image::FromFile("../graphical_interface/image.jpg");

			SetupGridView();
			
			
		}
	private: 
		System::Void SetupGridView()
		{	
			DataGridViewButtonColumn^ derivativeColumn = gcnew DataGridViewButtonColumn();
			derivativeColumn->HeaderText = "Производная";

			DataGridViewButtonColumn^ deleteColumn = gcnew DataGridViewButtonColumn();
			deleteColumn->HeaderText = "Удалить";
			deleteColumn->Text = "X";
			deleteColumn->UseColumnTextForButtonValue = true;

			polynomialGridView->Columns->Add("Name", "Имя");
			polynomialGridView->Columns->Add("Polynom", "Полином");
			polynomialGridView->Columns->Add(derivativeColumn);
			polynomialGridView->Columns->Add(deleteColumn);
		}
	private:
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
	private: 
		System::Void polynomialGridView_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
		{	
		
			if (e->ColumnIndex == 3) // Нажали на колонку с кнопками "Удалить"
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
			/*if (e->ColumnIndex == 2) // Производная
			{
				System::String^ polyName = polynomialGridView->Rows[e->RowIndex]->Cells[0]->Value->ToString();
				System::String^ pol = polynomialGridView->Rows[e->RowIndex]->Cells[1]->Value->ToString();
				std::string name = msclr::interop::marshal_as<std::string>(polyName);
				Polynom polynom = table.find(name);
				table.delete_rec(name);
				arr_table.delete_rec(name);

				Polynom new_polynom = polynom.derivative('x');
				table.insert(name, new_polynom);
				arr_table.insert(name, new_polynom);

				polynomialGridView->Rows[e->RowIndex]->Cells[0]->Value = polyName;
				polynomialGridView->Rows[e->RowIndex]->Cells[1]->Value = gcnew System::String(new_polynom.GetInfix().c_str());
			}*/
		}

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
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->polynomialGridView = (gcnew System::Windows::Forms::DataGridView());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->polynomialGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(137, 81);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(366, 31);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(137, 155);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(366, 31);
			this->textBox2->TabIndex = 1;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(137, 619);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(366, 31);
			this->textBox3->TabIndex = 2;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
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
			this->polynomialGridView->Location = System::Drawing::Point(528, 81);
			this->polynomialGridView->Name = L"polynomialGridView";
			this->polynomialGridView->ReadOnly = true;
			this->polynomialGridView->RowHeadersWidth = 82;
			this->polynomialGridView->RowTemplate->Height = 33;
			this->polynomialGridView->Size = System::Drawing::Size(1257, 642);
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
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Name = L"MyForm";
			this->Text = L"Polynom";
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
};
}
