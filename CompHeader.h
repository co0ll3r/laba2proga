#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#pragma once

class COMP{
public:
	std::string ProcName; // Brand name
	std::string ProcType; // Specification
	std::string Graphics; // Graphic Card
	double GraphicVolume;
	double ClockSpeed;
	double RAM;
	double Storage;
};

class RECORD{
public:
	COMP CompInfo;
	double CompCost;
	int CompInStock;
};

class workComputers {
	public:
		workComputers(int size = 0) : SizeOfMassive(size), CapabilitiesComp(SizeOfMassive ? new RECORD[SizeOfMassive]() : nullptr) {} 
		~workComputers() { delete [] CapabilitiesComp; }
		workComputers(workComputers&);
		workComputers operator=(workComputers&);

		void testCopyConstructor();
		void testCopyOperator();

		void InputFromFile();
		void OutputInFile();
		void Add_comp();
		void Delete_comp();
		void showInfo();
		void swapElementsInMassive(unsigned);
		void SortProcTypeAndClock();
		void SortProcName();
		void SortPrice();
		void SortRAM();
		void SearchPrice();
		void SearchHddVolume();
		void SearchBrandTypeRamETC();
	private:
		int SizeOfMassive; 
		RECORD* CapabilitiesComp;
};

