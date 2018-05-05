#include "CompHeader.h"

workComputers::workComputers(workComputers& copy){
	SizeOfMassive = copy.SizeOfMassive;
	if (SizeOfMassive == 0){
		std::cout << "n != 0!!!! в конструкторе копирования";
		exit(-1);
	}
	CapabilitiesComp = new RECORD[SizeOfMassive];
	if (CapabilitiesComp == NULL)
	{
		std::cout << "Нет места в конструкторе копирования";
		exit(-1);
	}
	for (int i = 0; i < SizeOfMassive; i++)
		CapabilitiesComp[i] = copy.CapabilitiesComp[i];
}

workComputers workComputers::operator=(workComputers& copy){
	if (this == &copy){
		return *this;
	}
	RECORD* MassRecordCopy = new RECORD[copy.SizeOfMassive];
	if (MassRecordCopy == NULL)
	{
		std::cout << "Не хватает места при иницииализации в операторе копирования\n";
		exit(-1);
	}	
	for (int i = 0; i < copy.SizeOfMassive; i++)
	{
		MassRecordCopy[i] = copy.CapabilitiesComp[i];
	}
	if (CapabilitiesComp != NULL)
		delete [] CapabilitiesComp;
	CapabilitiesComp = MassRecordCopy;	
	SizeOfMassive = copy.SizeOfMassive;
	MassRecordCopy = NULL;
	return *this;
}

void workComputers::testCopyOperator(){
	workComputers eg;
	eg.InputFromFile();
	eg.showInfo();
	if (true){
		workComputers egNumber2;
		egNumber2.InputFromFile();
		egNumber2.showInfo();
		eg = egNumber2;
	}
	eg.showInfo();
}

void workComputers::testCopyConstructor(){
	workComputers eg;
	eg.InputFromFile();
	eg.showInfo();
	workComputers egNumber2 = eg;
	egNumber2.showInfo();
}

void workComputers::InputFromFile(){
	std::string file;
	std::cout << "Введите имя файла для чтения\n";
	std::cin >> file;
	std::ifstream fin;
	fin.open(file);
	if (fin.fail()){
		std::cout << file << " не удалось создать файл\n";
		return;
	}
	RECORD ab;	
	RECORD* CopyCapComp;
	int i = -1;
	char end = '1';
	while(end != '\0'){
		if (fin.fail()) 
			break;
		i++;
		fin >> ab.CompCost >> ab.CompInStock >>
			ab.CompInfo.ProcName >> ab.CompInfo.ProcType  >>  
			ab.CompInfo.ClockSpeed >> ab.CompInfo.Graphics >>
			ab.CompInfo.GraphicVolume >>
			ab.CompInfo.RAM >> ab.CompInfo.Storage >> end;

//		if (i == 0 && SizeOfMassive != 0)

		CopyCapComp = new RECORD[i + 1];
		for (int j = 0; j < i; j++)
			if (CapabilitiesComp != NULL)
				CopyCapComp[j] = CapabilitiesComp[j];
		CopyCapComp[i] = ab;
		if (CapabilitiesComp != NULL)
			delete [] CapabilitiesComp;
		CapabilitiesComp = CopyCapComp;
		CopyCapComp = NULL;
		// доделай ввод	
	}
	SizeOfMassive = ++i;
}

void workComputers::OutputInFile(){
	std::string file;
	std::cout << "Введите имя файла для сохранения\n";
	std::cin >> file;
	std::ofstream fout;
	fout.open(file);
	if (fout.fail()){
		std::cout << file << " не удалось открыть файл\n";
		return;
	}
	fout << std::setfill('-') << std::setw(129) << "\n" <<
	     "|Номер| Цена | Кол. |                 Процессор                    |              Видеокарта           | ОЗУ | Размер жесткого |\n" <<
             "|     |      |      |----------------------------------------------|-----------------------------------|     |                 |\n" << 
	     "|     |(Руб.)|(штук)|    Название    |        Тип        | Частота |        Название        | Объём Гб |  Гб |      (Гб)       |\n" <<
	             std::setw(129) << "\n"; 
	for (int i = 0; i < SizeOfMassive; i++){
		fout << std::setfill(' ') <<
		   "|" << std::setw(5) << i + 1 << "|" << std::setw(6) <<CapabilitiesComp[i].CompCost << "|" 
		   << std::setw(6) << CapabilitiesComp[i].CompInStock << 
		     "|" << std::setw(16) << CapabilitiesComp[i].CompInfo.ProcName << "|" << std::setw(19) <<
		     CapabilitiesComp[i].CompInfo.ProcType << "|" << std::setw(9) << CapabilitiesComp[i].CompInfo.ClockSpeed << "|" 
		     << std::setw(24) << CapabilitiesComp[i].CompInfo.Graphics << "|" << std::setw(10) << CapabilitiesComp[i].CompInfo.GraphicVolume << "|" << std::setw(5) << 
		     CapabilitiesComp[i].CompInfo.RAM << "|" << std::setw(17) << CapabilitiesComp[i].CompInfo.Storage << "|\n";
		fout << std::setfill('-') << std::setw(129) << "\n"; 
	}
}

void workComputers::Add_comp(){
	RECORD add;
	std::cout << "Введите марку процессора: ";
	std::cin >> add.CompInfo.ProcName;
	std::cout << "Введите тип процессора(хар-ки): ";
	std::cin >> add.CompInfo.ProcType; 
	std::cout << "Введите частоту процессора: ";
	std::cin >> add.CompInfo.ClockSpeed; 
	std::cout << "Введите название видеокарты: ";
	std::cin >> add.CompInfo.Graphics;
	std::cout << "Введите объем видеокарты: ";
	std::cin >> add.CompInfo.GraphicVolume;
	std::cout << "Введите объем ОЗУ: ";
	std::cin >> add.CompInfo.RAM; 
	std::cout << "Введите объем жесткого диска: "; 
	std::cin >> add.CompInfo.Storage; 
	std::cout << "Введите цену: ";
	std::cin >> add.CompCost;
	std::cout << "Введите количество компьютеров на складе: ";
	std::cin >> add.CompInStock;
	RECORD* CopyCapComp = new RECORD[SizeOfMassive + 1];
	if (CopyCapComp == NULL)
	{
		std::cout << "Ошибка выделения памяти при добавлении компьютера!\n";
		exit(-1);
	}
	for (int j = 0; j < SizeOfMassive; j++)
		if (CapabilitiesComp != NULL)
			CopyCapComp[j] = CapabilitiesComp[j];
	CopyCapComp[SizeOfMassive] = add;
	if (CapabilitiesComp != NULL)
		delete [] CapabilitiesComp;
	CapabilitiesComp = CopyCapComp;
	SizeOfMassive++;
	CopyCapComp = NULL;

}

void workComputers::Delete_comp(){
	if (CapabilitiesComp == NULL)
	{
		std::cout << "Загрузите данные(массив элементов), т.к. массив пуст";
		return;	
	}
	int n;
	char ch;
	showInfo();
	std::cout << "Введите номер строки для удаления: ";
	std::cin >> n;
	if (n < 1 || n > SizeOfMassive){
		std::cout << " нет такой строки\n";
		return;
	}
	n--;
	std::cout << " удалить строку(press y):";
	std::cin >> ch;
	if (ch == 'y' || ch == 'Y'){
		RECORD* CopyCapComp = new RECORD[SizeOfMassive - 1];
		int i, j;
		for (i = 0; i < n; i++)
			CopyCapComp[i] = CapabilitiesComp[i];
		for (i = n + 1, j = n; i < SizeOfMassive; i++, j++)
			CopyCapComp[j] = CapabilitiesComp[i];
		if (CapabilitiesComp != NULL)
			delete [] CapabilitiesComp;
		CapabilitiesComp = CopyCapComp;
		CopyCapComp = NULL;
		SizeOfMassive--;
	}
}

void workComputers::showInfo(){
	std::cout << std::setfill('-') << std::setw(129) << "\n" <<
	     "|Номер| Цена | Кол. |                 Процессор                    |              Видеокарта           | ОЗУ | Размер жесткого |\n" <<
             "|     |      |      |----------------------------------------------|-----------------------------------|     |                 |\n" << 
	     "|     |(Руб.)|(штук)|    Название    |        Тип        | Частота |        Название        | Объём Гб |  Гб |      (Гб)       |\n" <<
	             std::setw(129) << "\n"; 
	for (int i = 0; i < SizeOfMassive; i++){
		std::cout << std::setfill(' ') <<
		   "|" << std::setw(5) << i + 1 << "|" << std::setw(6) <<CapabilitiesComp[i].CompCost << "|" 
		   << std::setw(6) << CapabilitiesComp[i].CompInStock << 
		     "|" << std::setw(16) << CapabilitiesComp[i].CompInfo.ProcName << "|" << std::setw(19) <<
		     CapabilitiesComp[i].CompInfo.ProcType << "|" << std::setw(9) << CapabilitiesComp[i].CompInfo.ClockSpeed << "|" 
		     << std::setw(24) << CapabilitiesComp[i].CompInfo.Graphics << "|" << std::setw(10) << CapabilitiesComp[i].CompInfo.GraphicVolume << "|" << std::setw(5) << 
		     CapabilitiesComp[i].CompInfo.RAM << "|" << std::setw(17) << CapabilitiesComp[i].CompInfo.Storage << "|\n";
		std::cout << std::setfill('-') << std::setw(129) << "\n"; 
	}
}

void workComputers::swapElementsInMassive(unsigned index){
	RECORD temp = CapabilitiesComp[index];
	CapabilitiesComp[index] = CapabilitiesComp[index - 1];
	CapabilitiesComp[index - 1] = temp;
}

void workComputers::SortProcTypeAndClock(){
	std::cout << "Сортировка по типу процессора и частоте: \n";
	unsigned n = SizeOfMassive; 
	bool flag;
	do{
		flag = false;
		for (unsigned i = 1; i < n; i++)
		{
			if (CapabilitiesComp[i].CompInfo.ProcType.compare(CapabilitiesComp[i - 1].CompInfo.ProcType) < 0)
			{
				swapElementsInMassive(i);
				flag = true;
			}
			else if (CapabilitiesComp[i].CompInfo.ProcType.compare(CapabilitiesComp[i - 1].CompInfo.ProcType) == 0 &&
				 CapabilitiesComp[i].CompInfo.ClockSpeed < CapabilitiesComp[i - 1].CompInfo.ClockSpeed)	
			{
				swapElementsInMassive(i);
				flag = true;
			}
		}
		n--;
	} while (flag);
	showInfo();
}

void workComputers::SortProcName(){
	std::cout << "Сортировка по названию процессора: \n";
	unsigned n = SizeOfMassive; 
	bool flag;
	do{
		flag = false;
		for (unsigned i = 1; i < n; i++)
		{
			if (CapabilitiesComp[i].CompInfo.ProcName.compare(CapabilitiesComp[i - 1].CompInfo.ProcName) < 0)
			{
				swapElementsInMassive(i);
				flag = true;
			}
			else if (CapabilitiesComp[i].CompInfo.ProcName.compare(CapabilitiesComp[i - 1].CompInfo.ProcName) == 0 &&
					CapabilitiesComp[i].CompInfo.ProcType.compare(CapabilitiesComp[i - 1].CompInfo.ProcType) < 0)
			{
				swapElementsInMassive(i);
				flag = true;
			}
		}
		n--;
	} while (flag);
	showInfo();
}

void workComputers::SortPrice(){
	std::cout << "Сортировка по цене: \n";
	bool flag;
	unsigned n = SizeOfMassive; 
	do{
		flag = false;
		for (unsigned i = 1; i < n; i++)
		{
			if (CapabilitiesComp[i - 1].CompCost > CapabilitiesComp[i].CompCost){
				swapElementsInMassive(i);
				flag = true;
			}
		}
		n--;
	} while(flag);
	showInfo();
}

void workComputers::SearchPrice(){
	if (CapabilitiesComp == NULL)
	{
		std::cout << "Загрузите массив \n";
		return;
	}
	double BottomBorder, TopBorder;
	std::cout << "Введите нижнюю границу цены(нестрогое): ";
	std::cin >> BottomBorder;
	std::cout << "Введите верхнюю границу цены(нестрогое): ";
	std::cin >> TopBorder;
	workComputers SearchResult;
	std::vector<int> CollectIndexes; // Второй вариант со сбором индеков
	for (int i = 0; i < SizeOfMassive; i++)
	{
		if (BottomBorder <= CapabilitiesComp[i].CompCost && CapabilitiesComp[i].CompCost <= TopBorder)
		{
			CollectIndexes.push_back(i);
	//		std::cout << "i= " << i << "\n";
			// Есть два варианта: 1) вектор собирающий индексы; 2) перераспределение памяти каждыый раз
		}	
	}
	if (CollectIndexes.size() == 0)
	{
		std::cout << "Не найдено!\n";
		return;
	}
	SearchResult.SizeOfMassive = CollectIndexes.size();
	std::cout << SearchResult.SizeOfMassive << " size\n";
	SearchResult.CapabilitiesComp = new RECORD[SearchResult.SizeOfMassive];
	for (int i = 0; i < SearchResult.SizeOfMassive; i++)
		SearchResult.CapabilitiesComp[i] = CapabilitiesComp[CollectIndexes[i]];
	SearchResult.SortProcTypeAndClock();
	char ch;
	std::cout << "Желаете сохранить результаты поиска в файл?(y/n)\n";
	std::cin >> ch;
	if (ch == 'y' || ch == 'Y')
		SearchResult.OutputInFile();
}
void workComputers::SortRAM(){
	std::cout << "Сортировка по ОЗУ: \n";
	bool flag;
	unsigned n = SizeOfMassive; 
	do{
		flag = false;
		for (unsigned i = 1; i < n; i++)
		{
			if (CapabilitiesComp[i - 1].CompInfo.RAM> CapabilitiesComp[i].CompInfo.RAM){
				swapElementsInMassive(i);
				flag = true;
			}
		}
		n--;
	} while(flag);
	showInfo();
}

void workComputers::SearchHddVolume(){
	if (CapabilitiesComp == NULL)
	{
		std::cout << "Загрузите массив \n";
		return;
	}
	double BottomBorder, TopBorder;
	std::cout << "Введите нижнюю границу размера памяти(нестрогое): ";
	std::cin >> BottomBorder;
	std::cout << "Введите верхнюю границу размера памяти(нестрогое): ";
	std::cin >> TopBorder;
	workComputers SearchResult;
	std::vector<int> CollectIndexes; // Второй вариант со сбором индеков
	for (int i = 0; i < SizeOfMassive; i++)
	{
		if (BottomBorder <= CapabilitiesComp[i].CompInfo.Storage && CapabilitiesComp[i].CompInfo.Storage <= TopBorder)
			CollectIndexes.push_back(i);
	}
	if (CollectIndexes.size() == 0)
	{
		std::cout << "Не найдено!\n";
		return;
	}
	SearchResult.SizeOfMassive = CollectIndexes.size();
	std::cout << SearchResult.SizeOfMassive << " size\n";
	SearchResult.CapabilitiesComp = new RECORD[SearchResult.SizeOfMassive];
	for (int i = 0; i < SearchResult.SizeOfMassive; i++)
		SearchResult.CapabilitiesComp[i] = CapabilitiesComp[CollectIndexes[i]];
	SearchResult.SortRAM();
	char ch;
	std::cout << "Желаете сохранить результаты поиска в файл?(y/n)\n";
	std::cin >> ch;
	if (ch == 'y' || ch == 'Y')
		SearchResult.OutputInFile();
}

void workComputers::SearchBrandTypeRamETC(){
	if (CapabilitiesComp == NULL)
	{
		std::cout << "Загрузите массив \n";
		return;
	}
	std::string NameOfProc, TypeOfProc;
	double BottomBorder, TopBorder, BBRAM, TBRAM, BBVideo, TBVideo;
	std::cout << "Введите название марки процессора ";
	std::cin >> NameOfProc;
	std::cout << "Введите тип процессора ";
	std::cin >> TypeOfProc;
	std::cout << "Введите нижнюю границу размера памяти hdd(нестрогое): ";
	std::cin >> BottomBorder;
	std::cout << "Введите верхнюю границу размера памяти hdd(нестрогое): ";
	std::cin >> TopBorder;
	std::cout << "Введите нижнюю границу размера ОЗУ(нестрогое): ";
	std::cin >> BBRAM;
	std::cout << "Введите верхнюю границу размера ОЗУ(нестрогое): ";
	std::cin >> TBRAM;
	std::cout << "Введите нижнюю границу размера видеопамяти(нестрогое): ";
	std::cin >> BBVideo;
	std::cout << "Введите верхнюю границу размера видеопамяти(нестрогое): ";
	std::cin >> TBVideo;
	workComputers SearchResult;
	std::vector<int> CollectIndexes; // Второй вариант со сбором индеков
	for (int i = 0; i < SizeOfMassive; i++)
	{
		if (BottomBorder <= CapabilitiesComp[i].CompInfo.Storage && CapabilitiesComp[i].CompInfo.Storage <= TopBorder && 
			NameOfProc == CapabilitiesComp[i].CompInfo.ProcName && CapabilitiesComp[i].CompInfo.ProcType == TypeOfProc &&
		       	BBRAM <= CapabilitiesComp[i].CompInfo.RAM && CapabilitiesComp[i].CompInfo.RAM <= TBRAM &&
		      	BBVideo<= CapabilitiesComp[i].CompInfo.GraphicVolume && CapabilitiesComp[i].CompInfo.GraphicVolume <= TBVideo)

				CollectIndexes.push_back(i);
	}
	if (CollectIndexes.size() == 0)
	{
		std::cout << "Не найдено!\n";
		return;
	}
	SearchResult.SizeOfMassive = CollectIndexes.size();
	std::cout << SearchResult.SizeOfMassive << " size\n";
	SearchResult.CapabilitiesComp = new RECORD[SearchResult.SizeOfMassive];
	for (int i = 0; i < SearchResult.SizeOfMassive; i++)
		SearchResult.CapabilitiesComp[i] = CapabilitiesComp[CollectIndexes[i]];
	SearchResult.showInfo();
	char ch;
	std::cout << "Желаете сохранить результаты поиска в файл?(y/n)\n";
	std::cin >> ch;
	if (ch == 'y' || ch == 'Y')
		SearchResult.OutputInFile();

}
