#include "CompHeader.h"

void GetMenu(workComputers& ExampleComputer, bool& ExitFlag){
	int SwitchChoose = 1;
	std::cout << "\033c"; // clear terminal
	//system("clear");
	std::cout << "1. Загрузка файла\n2. Сохранение результатов обработки в файл\n" <<
		     "3. Добавление записи\n4. Удаление записи\n" <<
		     "5. Вывод на экран\n6. Сортировка по типу процессора и тактовой частоте\n" <<
		     "7. Алфавитная сортировка по названию марки\n8. Числовая сортировка по цене\n" << 
		     "9. Поиск по цене\n10. Поиск по объему жесткого диска\n11. Поиск по названию марки, типу процессора," << 
	       	     "объему ОЗУ, объему ЖД и объему видеопамяти\n" <<
		     "12. Тестирование оператора присваивания\n13. Тестирование конструктора копирования\n";

	while (SwitchChoose == 1){
		std::cout << "Введите пункт меню: ";
		std::cin >> SwitchChoose;
		std::cout << "\n";
		switch(SwitchChoose){
			case 1: ExampleComputer.InputFromFile(); break;
			case 2: ExampleComputer.OutputInFile(); break;
			case 3: ExampleComputer.Add_comp(); break;
			case 4: ExampleComputer.Delete_comp(); break;
			case 5: ExampleComputer.showInfo(); break;
			case 6: ExampleComputer.SortProcTypeAndClock(); break;
			case 7: ExampleComputer.SortProcName(); break; 	
			case 8:	ExampleComputer.SortPrice(); break;
			case 9: ExampleComputer.SearchPrice(); break;
			case 10: ExampleComputer.SearchHddVolume(); break;
			case 11: ExampleComputer.SearchBrandTypeRamETC(); break;
			case 12: ExampleComputer.testCopyOperator(); break;
			case 13: ExampleComputer.testCopyConstructor(); break;
			default: std::cout << "Закрытие программы\n"; ExitFlag = false;	
		}
		//  	std::cout << "Нажмите любую клавишу для продолжения ";
		//	system("read -s -N 1");
		std::cout << "\nВведите 1 для повторного выбора пункта меню(без очистки экрана): ";
		std::cin >> SwitchChoose; // 
	}
//	std::cin.get();

}

int main(){
	workComputers example;
	bool ExitFlag = true;
	while(ExitFlag){
		GetMenu(example, ExitFlag);
	}
	std::cout << "\n press something to exit\n";
	int a;
	std::cin >> a;
	return 0;
}
