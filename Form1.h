#pragma once
#include <msclr\marshal_cppstd.h>
#include <vector>
#include <fstream>
#include <iostream>

std::vector<short> wavData;
std::vector<std::string> coefDataString;
std::vector<float> coefData;
std::vector<float> outputData;
std::vector<short>outputDatapushed;
std::string wavName, coefName, outputName;
signed short high;

struct WavHeader {
	char riffId[4];
	unsigned long headerChunkSize;
	char waveId[4];
	char formatChunkId[4];
	unsigned long formatChunkSize;
	unsigned short compressionCode;
	unsigned short numberOfChannels;
	unsigned long samplesRate;
	unsigned long byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char dataChunkId[4];
	unsigned long dataChunkSize;
}wavHeader;
namespace CppCLRWinformsProjekt {

	//using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			
		}

	protected:
	
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(23, 21);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(124, 41);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Open WAV file";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(23, 78);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(124, 44);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Open FIR coefficients";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(153, 21);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(124, 41);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Filter WAV file";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(153, 78);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(124, 44);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Save filtered WAV";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(304, 137);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"FIR filter";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {//OPEN WAV
		System::String^ store1;
		System::IO::Stream^ myStream;
		System::Windows::Forms::OpenFileDialog^ openFileDialog1 = gcnew System::Windows::Forms::OpenFileDialog;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) { //== System::Windows::Forms::DialogResult::OK) {
			if ((myStream = openFileDialog1->OpenFile()) != nullptr) {
				store1 = openFileDialog1->InitialDirectory + openFileDialog1->FileName;
				wavName = msclr::interop::marshal_as<std::string>(store1);
				System::Windows::Forms::MessageBox::Show(store1);
				myStream->Close();
			}
		}
		//creating filestream-opening and file-seeking to start of file
		std::ifstream audioFile;
		audioFile.open(wavName, std::ios::binary);
		audioFile.seekg(0, std::ios::beg);
		//reading header into struct for storage
		audioFile.read((char*)&wavHeader, sizeof(WavHeader));
		//go to beginning of data
		audioFile.seekg(sizeof(WavHeader), std::ios::beg);
		//reading in the data into a vector of shorts
		while (!audioFile.eof()) {
			audioFile.read((char*)&high, 2);
			wavData.push_back(high);
		}
	}
    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {//OPEN COEFF
			System::String^ store2;
			System::IO::Stream^ myStream2;
			System::Windows::Forms::OpenFileDialog^ openFileDialog2 = gcnew System::Windows::Forms::OpenFileDialog;
			if (openFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK) { //== System::Windows::Forms::DialogResult::OK) {
				if ((myStream2 = openFileDialog2->OpenFile()) != nullptr) {
					store2 = openFileDialog2->InitialDirectory + openFileDialog2->FileName;
					coefName = msclr::interop::marshal_as<std::string>(store2);
					System::Windows::Forms::MessageBox::Show(store2);
					myStream2->Close();
				}
			}
			//open coefficients and seek beginning of file 
			std::ifstream coefFile;
			std::string str;
			coefFile.open(coefName, std::ios::in);
			coefFile.seekg(0, std::ios::beg);

			//reading coeff into vector, removing the leading space
			while (std::getline(coefFile, str)) {
				str.erase(0, str.find_first_not_of(' '));
				coefDataString.push_back(str);
			}
			//turning string to floats
			for (auto i : coefDataString) {
				coefData.push_back(std::stof(i));
			}

			std::cout << "Breakpoint2" << std::endl;
		}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {//perform convolution
		outputData.resize(wavData.size() + coefData.size() - 1);
		int wavsize = (int)wavData.size();
		int coefsize = (int)coefData.size();
		int outsize = (int)outputData.size();
		//waiting
		System::String^ haha = "Please wait for filtering to finish";
		System::Windows::Forms::MessageBox::Show(haha);
		//convolution algo
		for (int n = 0; n < wavsize; ++n) {
			for (int k = 0; k < coefsize; ++k) {
				if ((n - k) >= 0) {
					outputData[n] += coefData[k] * wavData[n - k];
				}
			}
		}
		//pushback the outputdata to only use the positive frequencies
		for (auto i = (coefsize - 1); i < outsize; ++i) {
			outputDatapushed.push_back((short)outputData[i]);
		}

		System::String^ holdoon = "Filtering done";
		System::Windows::Forms::MessageBox::Show(holdoon);

		std::cout << "Breakpoint3" << std::endl;
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {//write to file
		System::String^ savelocation;
		System::IO::Stream^ savestream;
		System::Windows::Forms::SaveFileDialog^ saveFileDialog = gcnew System::Windows::Forms::SaveFileDialog;
		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if ((savestream = saveFileDialog->OpenFile()) != nullptr) {
				savelocation = saveFileDialog->InitialDirectory + saveFileDialog->FileName;
				outputName = msclr::interop::marshal_as<std::string>(savelocation);
				System::Windows::Forms::MessageBox::Show(savelocation);
				savestream->Close();
			}
		}
		//saving the filtered data
		std::ofstream outputFile;
		outputFile.open(outputName + ".wav", std::ios::binary);
		outputFile.write((char*)&wavHeader, sizeof(WavHeader));
		for (int i = 0; i < outputDatapushed.size(); ++i) {
			outputFile.write((char*)&outputDatapushed[i], 2);
		}

		std::cout << "Breakpoint4" << std::endl;
	}
	
 };
}
