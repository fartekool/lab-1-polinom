#pragma once
#include <string>
#include <msclr\marshal_cppstd.h>
#include "../polynom/polynom.h"
#include "../polynomial_algebra/expression.h"
#include "../tables/tables_manager.h"
namespace graphicalinterface {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	Tables_manager<string, string> table;
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		
	public:
		MyForm(void)
		{	
			
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->BackColor = Color::FromArgb(130, 171, 217);
			this->Width = 800;
			this->Height = 450;
			this->StartPosition = FormStartPosition::CenterScreen;
			this->BackgroundImage = Image::FromFile("../graphical_interface/image.jpg");

			polynomialGridView->ColumnCount = 2;
			polynomialGridView->Columns[0]->Name = "Имя";
			polynomialGridView->Columns[1]->Name = "Полином";
			
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ polynomialGridView;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{	
			
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->polynomialGridView = (gcnew System::Windows::Forms::DataGridView());
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
			this->polynomialGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->polynomialGridView->Location = System::Drawing::Point(591, 81);
			this->polynomialGridView->Name = L"polynomialGridView";
			this->polynomialGridView->RowHeadersWidth = 82;
			this->polynomialGridView->RowTemplate->Height = 33;
			this->polynomialGridView->Size = System::Drawing::Size(761, 642);
			this->polynomialGridView->TabIndex = 4;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1364, 755);
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
		/*double num1, num2, result;
		num1 = System::Convert::ToDouble(textBox1->Text);
		num2 = System::Convert::ToDouble(textBox2->Text);
		result = Sum(num1, num2);

		textBox3->Text = System::Convert::ToString(result);*/
		String^ NAME = textBox1->Text;
		String^ POLYNOM = textBox2->Text;
		std::string name = msclr::interop::marshal_as<std::string>(textBox1->Text);
		std::string polynom = msclr::interop::marshal_as<std::string>(textBox2->Text);
		if(table.insert(name, polynom))
			polynomialGridView->Rows->Add(gcnew String(NAME), gcnew String(POLYNOM));
		else
			MessageBox::Show("Уже существует!");
	}
};
}
