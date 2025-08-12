//
// Created by gd182 on 09.08.2025.
//

#include "MainForm.h"

#include <cmath>
#include <codecvt>
#include <float.h>
#include <stdexcept>
#include <fstream>
#include <locale>


/**
 * Метод для создания главной формы приложения
 */
void MainForm::createForm()
{
	countRes = 0;
	numChart = 0;
	tableRes = nullptr;
	labelRes = nullptr;
	form = Application_CreateForm(Application);
    Form_SetCaption(form, (std::string(Application_GetTitle(Application)) + " - " + DefFileName).c_str());
    Form_SetPosition(form, poScreenCenter);
    Form_SetClientWidth(form, 660);
    Form_SetClientHeight(form, 623);
	Form_SetTag(form, reinterpret_cast<intptr_t>(this));
	SizeConstraints_SetMinWidth(Form_GetConstraints(form), 687);
	SizeConstraints_SetMinHeight(Form_GetConstraints(form), 682);
	Form_SetOnCloseQuery(form, st_formCloseQuery);


    createMenu();
    createButtons();
    createLabels();
    createEdits();
    createStringGrids();
	createScrollBox();
    createChart();
    createStatusBar();
	createDialogs();
	Form_SetOnResize(form, st_formResize);
}

/**
 * Пытается преобразовать строку в целое число (int)
 * @param str Входная строка для преобразования
 * @param outValue Ссылка на переменную, куда запишется результат при успехе
 * @return true - если преобразование прошло успешно
 * @return false - если строка не является числом или число вне диапазона int
 */
bool MainForm::tryStrToInt(const std::string& str, int& outValue) {
	try {
		size_t pos;
		outValue = std::stoi(str, &pos);
		return (pos == str.length()); // Проверяем, что вся строка преобразована
	} catch (const std::invalid_argument&) {
		return false; // Строка не является числом
	} catch (const std::out_of_range&) {
		return false; // Число вне диапазона int
	}
}

/**
 * Пытается преобразовать строку в число с плавающей точкой (float).
 * @param str - входная строка
 * @param outValue - ссылка на float, куда запишется результат
 * @return true - если преобразование успешно
 * @return false - если ошибка
 */
bool MainForm::tryStrToFloat(const std::string& str, float& outValue) {
	try {
		size_t pos;
		outValue = std::stof(str, &pos);
		return (pos == str.length()); // Проверяем, что вся строка обработана
	} catch (const std::invalid_argument&) {
		return false; // Строка не является числом
	} catch (const std::out_of_range&) {
		return false; // Число вне диапазона float
	}
}
/**
 * Создание меню
 */
void MainForm::createMenu() {
    mainMenu = MainMenu_Create(form);

    //Пункт "Файл"
    miFile = MenuItem_Create(mainMenu);
    MenuItem_SetCaption(miFile, "Файл");
    MenuItem_Add(MainMenu_GetItems(mainMenu), miFile);
    //Подпункт "Создать"
    miCreate = MenuItem_Create(miFile);
    MenuItem_SetCaption(miCreate, "Создать");
	MainMenu_SetTag(miCreate, reinterpret_cast<intptr_t>(this));
	MenuItem_SetOnClick(miCreate, st_miCreateClick);
	MenuItem_Add(miFile, miCreate);
    //Подпункт "Открыть"
    miOpen = MenuItem_Create(miFile);
    MenuItem_SetCaption(miOpen, "Открыть...");
	MainMenu_SetTag(miOpen, reinterpret_cast<intptr_t>(this));
	MenuItem_SetOnClick(miOpen, st_miOpenClick);
    MenuItem_Add(miFile, miOpen);
    //Разделительная полоса
    miDivLineFile1 = MenuItem_Create(miFile);
    MenuItem_SetCaption(miDivLineFile1, "-");
    MenuItem_Add(miFile, miDivLineFile1);
    //Подпункт "Сохранить"
    miSave = MenuItem_Create(miFile);
    MenuItem_SetCaption(miSave, "Сохранить");
    MenuItem_SetEnabled(miSave, FALSE);
	MainMenu_SetTag(miSave, reinterpret_cast<intptr_t>(this));
	MenuItem_SetOnClick(miSave, st_miSaveClick);
    MenuItem_Add(miFile, miSave);
    //Подпункт "Сохранить как"
    miSaveAs = MenuItem_Create(miFile);
    MenuItem_SetCaption(miSaveAs, "Сохранить как...");
	MainMenu_SetTag(miSaveAs, reinterpret_cast<intptr_t>(this));
	MenuItem_SetOnClick(miSaveAs, st_miSaveAsClick);
    MenuItem_Add(miFile, miSaveAs);
    //Разделительная полоса
    miDivLineFile2 = MenuItem_Create(miFile);
    MenuItem_SetCaption(miDivLineFile2, "-");
    MenuItem_Add(miFile, miDivLineFile2);
    //Подпункт "Выход"
    miExit = MenuItem_Create(miFile);
    MenuItem_SetCaption(miExit, "Выход");\
	MainMenu_SetTag(miExit, reinterpret_cast<intptr_t>(this));
	MenuItem_SetOnClick(miExit, st_miCloseClick);
    MenuItem_Add(miFile, miExit);

    //Пункт "Редактировать"
    miEdit = MenuItem_Create(mainMenu);
    MenuItem_SetCaption(miEdit, "Редактировать");
    MenuItem_Add(MainMenu_GetItems(mainMenu), miEdit);
    //Подпункт "Добавить вместимость"
    miAddCapacity = MenuItem_Create(miEdit);
    MenuItem_SetCaption(miAddCapacity, "Добавить вместимость");
    MainMenu_SetTag(miAddCapacity, reinterpret_cast<intptr_t>(this));
    MenuItem_SetOnClick(miAddCapacity, st_miAddCapacityClick);
    MenuItem_Add(miEdit, miAddCapacity);
    //Подпункт "Удалить вместимость"
    miDelCapacity = MenuItem_Create(miEdit);
    MenuItem_SetCaption(miDelCapacity, "Удалить вместимость");
    MenuItem_SetEnabled(miDelCapacity, FALSE);
    MainMenu_SetTag(miDelCapacity, reinterpret_cast<intptr_t>(this));
    MenuItem_SetOnClick(miDelCapacity, st_miDelCapacityClick);
    MenuItem_Add(miEdit, miDelCapacity);
    //Разделительная полоса
    miDivLineEdit1 = MenuItem_Create(miEdit);
    MenuItem_SetCaption(miDivLineEdit1, "-");
    MenuItem_Add(miEdit, miDivLineEdit1);
    //Подпункт "Добавить число дверей"
    miAddNumDoors = MenuItem_Create(miEdit);
    MenuItem_SetCaption(miAddNumDoors, "Добавить число дверей");
    MainMenu_SetTag(miAddNumDoors, reinterpret_cast<intptr_t>(this));
    MenuItem_SetOnClick(miAddNumDoors, st_miAddNumDoorsClick);
    MenuItem_Add(miEdit, miAddNumDoors);
    //Подпункт "Удалить число дверей"
    miDelNumDoors = MenuItem_Create(miEdit);
    MenuItem_SetCaption(miDelNumDoors, "Удалить число дверей");
    MenuItem_SetEnabled(miDelNumDoors, FALSE);
    MainMenu_SetTag(miDelNumDoors, reinterpret_cast<intptr_t>(this));
    MenuItem_SetOnClick(miDelNumDoors, st_miDelNumDoorsClick);
    MenuItem_Add(miEdit, miDelNumDoors);
    //Разделительная полоса
    miDivLineEdit2 = MenuItem_Create(miEdit);
    MenuItem_SetCaption(miDivLineEdit2, "-");
    MenuItem_Add(miEdit, miDivLineEdit2);
    //Подпункт "Добавить коэф. входа и выхода"
    miAddCoefQuan = MenuItem_Create(miEdit);
    MenuItem_SetCaption(miAddCoefQuan, "Добавить коэф. входа и выхода");
    MainMenu_SetTag(miAddCoefQuan, reinterpret_cast<intptr_t>(this));
    MenuItem_SetOnClick(miAddCoefQuan, st_miAddCoefQuanClick);
    MenuItem_Add(miEdit, miAddCoefQuan);
    //Подпункт "Удалить коэф. входа и выхода"
    miDelCoefQuan = MenuItem_Create(miEdit);
    MenuItem_SetCaption(miDelCoefQuan, "Удалить коэф. входа и выхода");
    MenuItem_SetEnabled(miDelCoefQuan, FALSE);
    MainMenu_SetTag(miDelCoefQuan, reinterpret_cast<intptr_t>(this));
    MenuItem_SetOnClick(miDelCoefQuan, st_miDelCoefQuanClick);
    MenuItem_Add(miEdit, miDelCoefQuan);

    //Пункт "Результаты"
    miRes = MenuItem_Create(mainMenu);
    MenuItem_SetCaption(miRes, "Результаты");
    MenuItem_Add(MainMenu_GetItems(mainMenu), miRes);
    //Подпункт "Обработать данные"
    miCalcData = MenuItem_Create(miRes);
    MenuItem_SetCaption(miCalcData, "Обработать данные");
	MenuItem_SetTag(miCalcData, reinterpret_cast<intptr_t>(this));
	MenuItem_SetOnClick(miCalcData, st_miCalcDataClick);
    MenuItem_Add(miRes, miCalcData);

    Form_SetMenu(form, mainMenu);
}
/**
 * Создание кнопок
 */
void MainForm::createButtons() {
    //Кнопка "Обработать данные"
    bCalcData = Button_Create(form);
    Button_SetParent(bCalcData, form);
    Button_SetCaption(bCalcData, "Обработать данные");
    Button_SetWidth(bCalcData, 118);
    Button_SetHeight(bCalcData, 25);
    Button_SetTabOrder(bCalcData, 7);
    Button_SetLeft(bCalcData, 8);
    Button_SetTop(bCalcData, 331);
	Button_SetTag(bCalcData, reinterpret_cast<intptr_t>(this));
	Button_SetOnClick(bCalcData, st_bCalcDataClick);

    //Кнопка "Предыдущий график"
    bPrevChart = Button_Create(form);
    Button_SetParent(bPrevChart, form);
    Button_SetCaption(bPrevChart, "Предыдущий график");
    Button_SetWidth(bPrevChart, 121);
    Button_SetHeight(bPrevChart, 25);
    Button_SetTabOrder(bPrevChart, 9);
    Button_SetLeft(bPrevChart, 343);
    Button_SetTop(bPrevChart, Form_GetClientHeight(form) - 48);
    Button_SetEnabled(bPrevChart, FALSE);
	Button_SetTag(bPrevChart, reinterpret_cast<intptr_t>(this));
	Button_SetOnClick(bPrevChart, st_bPrevChartClick);

    //Кнопка "Следующий график"
    bNextChart = Button_Create(form);
    Button_SetParent(bNextChart, form);
    Button_SetCaption(bNextChart, "Следующий график");
    Button_SetWidth(bNextChart, 121);
    Button_SetHeight(bNextChart, 25);
    Button_SetTabOrder(bNextChart, 8);
    Button_SetLeft(bNextChart, Form_GetClientWidth(form) - 129);
    Button_SetTop(bNextChart, Form_GetClientHeight(form) - 48);
    Button_SetEnabled(bNextChart, FALSE);
	Button_SetTag(bNextChart, reinterpret_cast<intptr_t>(this));
	Button_SetOnClick(bNextChart, st_bNextChartClick);
}

/**
 * Создание подписей
 */
void MainForm::createLabels() {
    //Подпись исходных данных
    lInitData = Label_Create(form);
    Label_SetParent(lInitData, form);
    Label_SetCaption(lInitData, "Исходные данные");
    Label_SetWidth(lInitData, 91);
    Label_SetHeight(lInitData, 13);
    Label_SetLeft(lInitData, 8);
    Label_SetTop(lInitData, 2);

    //Подпись таблицы вместимости
    lCapGrid = Label_Create(form);
    Label_SetParent(lCapGrid, form);
    Label_SetCaption(lCapGrid, "Вместимость транспорта (чел):");
    Label_SetWidth(lCapGrid, 159);
    Label_SetHeight(lCapGrid, 13);
    Label_SetLeft(lCapGrid, 8);
    Label_SetTop(lCapGrid, 21);

    //подпись таблицы числа дверей
    lNumDorsGrid = Label_Create(form);
    Label_SetParent(lNumDorsGrid, form);
    Label_SetCaption(lNumDorsGrid, "Число дверей:");
    Label_SetWidth(lNumDorsGrid, 74);
    Label_SetHeight(lNumDorsGrid, 13);
    Label_SetLeft(lNumDorsGrid, 8);
    Label_SetTop(lNumDorsGrid, 116);

    //Подпись таблицы коэффициентов
    lcoefQuanGrid = Label_Create(form);
    Label_SetParent(lcoefQuanGrid, form);
    Label_SetCaption(lcoefQuanGrid, "Коэффициент, учитывающий количество выходящих и входящих пассажиров:");
    Label_SetWidth(lcoefQuanGrid, 407);
    Label_SetHeight(lcoefQuanGrid, 13);
    Label_SetLeft(lcoefQuanGrid, 8);
    Label_SetTop(lcoefQuanGrid, 211);

    //Подпись поля ввода времени входа и выхода
    lTimeE = Label_Create(form);
    Label_SetParent(lTimeE, form);
    Label_SetCaption(lTimeE, "Время выхода и входа одного пассажира, t0");
    Label_SetWidth(lTimeE, 231);
    Label_SetHeight(lTimeE, 13);
    Label_SetLeft(lTimeE, 8);
    Label_SetTop(lTimeE, 312);

    //Подпись поля ввода минимального интервала
    lMinInt = Label_Create(form);
    Label_SetParent(lMinInt, form);
    Label_SetCaption(lMinInt, "Минимальный интервал между транспортом (м), i");
    Label_SetWidth(lMinInt, 251);
    Label_SetHeight(lMinInt, 13);
    Label_SetLeft(lMinInt, 325);
    Label_SetTop(lMinInt, 312);

    //Подпись таблицы результатов
    lres = Label_Create(form);
    Label_SetParent(lres, form);
    Label_SetCaption(lres, "Минимальный интервал между транспортом (м), i");
    Label_SetWidth(lres, 118);
    Label_SetHeight(lres, 13);
    Label_SetLeft(lres, 8);
    Label_SetTop(lres, 362);

    //Подпись графика
    lChart = Label_Create(form);
    Label_SetParent(lChart, form);
    Label_SetCaption(lChart, "");
    Label_SetHeight(lChart, 13);
    Label_SetLeft(lChart, 352);
    Label_SetTop(lChart, 381);
}

/**
 * Создание полей ваода
 */
void MainForm::createEdits() {
    //Поле ввода времени входа и выхода
    eTimeE = Edit_Create(form);
    Edit_SetParent(eTimeE, form);
    Edit_SetTabOrder(eTimeE, 3);
    Edit_SetWidth(eTimeE, 68);
    Edit_SetHeight(eTimeE, 21);
    Edit_SetLeft(eTimeE, 252);
    Edit_SetTop(eTimeE, 309);
	Edit_SetTag(eTimeE, reinterpret_cast<intptr_t>(this));
	Edit_SetOnKeyPress(eTimeE, st_editDoubleKeyPress);

    //Поле ввода минимального интервала
    eMinInterval = Edit_Create(form);
    Edit_SetParent(eMinInterval, form);
    Edit_SetTabOrder(eMinInterval, 4);
    Edit_SetWidth(eMinInterval, 68);
    Edit_SetHeight(eMinInterval, 21);
    Edit_SetLeft(eMinInterval, 610);
    Edit_SetTop(eMinInterval, 309);
	Edit_SetTag(eMinInterval, reinterpret_cast<intptr_t>(this));
	Edit_SetOnKeyPress(eMinInterval, st_editDoubleKeyPress);
}

/**
 * Создание таблиц
 */
void MainForm::createStringGrids() {
    //Таблица вместимости
    capacityGrid = StringGrid_Create(form);
    StringGrid_SetParent(capacityGrid, form);
    StringGrid_SetTabOrder(capacityGrid, 0);Edit_SetWidth(eTimeE, 68);
    StringGrid_SetWidth(capacityGrid, 638);
    StringGrid_SetHeight(capacityGrid, 73);
    StringGrid_SetLeft(capacityGrid, 8);
    StringGrid_SetTop(capacityGrid, 40);
    StringGrid_SetColCount(capacityGrid, 2);
    StringGrid_SetRowCount(capacityGrid, 2);
    StringGrid_SetCells(capacityGrid, 0, 0, "№");
    StringGrid_SetCells(capacityGrid, 1, 0, "1");
    StringGrid_SetCells(capacityGrid, 0, 1, "\u03A9");
	StringGrid_SetOptions(capacityGrid, StringGrid_GetOptions(capacityGrid) << goEditing);
	StringGrid_SetTag(capacityGrid, reinterpret_cast<intptr_t>(this));
	StringGrid_SetOnKeyPress(capacityGrid, st_intGridKeyPress);

    //Таблица числа дверей
    numDoorsGrid = StringGrid_Create(form);
    StringGrid_SetParent(numDoorsGrid, form);
    StringGrid_SetTabOrder(numDoorsGrid, 1);
    StringGrid_SetWidth(numDoorsGrid, 638);
    StringGrid_SetHeight(numDoorsGrid, 73);
    StringGrid_SetLeft(numDoorsGrid, 8);
    StringGrid_SetTop(numDoorsGrid, 135);
    StringGrid_SetColCount(numDoorsGrid, 2);
    StringGrid_SetRowCount(numDoorsGrid, 2);
    StringGrid_SetCells(numDoorsGrid, 0, 0, "№");
    StringGrid_SetCells(numDoorsGrid, 1, 0, "1");
    StringGrid_SetCells(numDoorsGrid, 0, 1, "Кдв");
	StringGrid_SetOptions(numDoorsGrid, StringGrid_GetOptions(numDoorsGrid) << goEditing);
	StringGrid_SetTag(numDoorsGrid, reinterpret_cast<intptr_t>(this));
	StringGrid_SetOnKeyPress(numDoorsGrid, st_intGridKeyPress);

    //Таблица коэффициентов
    coefQuanGrid = StringGrid_Create(form);
    StringGrid_SetParent(coefQuanGrid, form);
    StringGrid_SetTabOrder(coefQuanGrid, 2);
    StringGrid_SetWidth(coefQuanGrid, 638);
    StringGrid_SetHeight(coefQuanGrid, 73);
    StringGrid_SetLeft(coefQuanGrid, 8);
    StringGrid_SetTop(coefQuanGrid, 230);
    StringGrid_SetColCount(coefQuanGrid, 2);
    StringGrid_SetRowCount(coefQuanGrid, 2);
    StringGrid_SetCells(coefQuanGrid, 0, 0, "№");
    StringGrid_SetCells(coefQuanGrid, 1, 0, "1");
    StringGrid_SetCells(coefQuanGrid, 0, 1, "Квв");
	StringGrid_SetOptions(coefQuanGrid, StringGrid_GetOptions(coefQuanGrid) << goEditing);
	StringGrid_SetTag(coefQuanGrid, reinterpret_cast<intptr_t>(this));
	StringGrid_SetOnKeyPress(coefQuanGrid, st_gridDoubleKeyPress);
}

/**
 * Создание скрол бокса
 */
void MainForm::createScrollBox() {
	//Скрол бокс результатов
	scrollBoxRes = ScrollBox_Create(form);
	ScrollBox_SetParent(scrollBoxRes, form);
	ScrollBox_SetTabOrder(scrollBoxRes, 6);
	ScrollBox_SetWidth(scrollBoxRes, 322);
	ScrollBox_SetHeight(scrollBoxRes, 217);
	ScrollBox_SetLeft(scrollBoxRes, 8);
	ScrollBox_SetTop(scrollBoxRes, 381);
}

/**
 * Создание графика
 */
void MainForm::createChart() {
    chart = Image_Create(form);
    Image_SetParent(chart, form);
    Image_SetWidth(chart, 294);
    Image_SetHeight(chart, 167);
    Image_SetLeft(chart, 352);
    Image_SetTop(chart, 400);
    Image_SetStretch(chart, true);
}

/**
 * Создание статус бара
 */
void MainForm::createStatusBar() {
    statusBar = StatusBar_Create(form);
    StatusBar_SetParent(statusBar, form);
    StatusBar_SetSimplePanel(statusBar, TRUE);
    StatusBar_SetSimpleText(statusBar, "");
    StatusBar_SetAlign(statusBar, alBottom);
}

/**
 * Создание диалогов
 */
void MainForm::createDialogs() {
	//создание диалога сохранения
	saveDialog = SaveDialog_Create(form);
	SaveDialog_SetDefaultExt(saveDialog, "bso");
	SaveDialog_SetFilter(saveDialog, "Файлы с исходными данными (*.bso)|*.bso|Все файлы (*.*)|*.*");
	SaveDialog_SetOptions(saveDialog, StringGrid_GetOptions(saveDialog) << ofOverwritePrompt << ofPathMustExist);
	SaveDialog_SetFileName(saveDialog, "");
	//создание диалога открытия
	openDialog = OpenDialog_Create(form);
	OpenDialog_SetDefaultExt(openDialog, "bso");
	OpenDialog_SetFilter(openDialog, "Файлы с исходными данными (*.bso)|*.bso|Все файлы (*.*)|*.*");
	OpenDialog_SetOptions(openDialog, StringGrid_GetOptions(openDialog) << ofFileMustExist);
	OpenDialog_SetFileName(openDialog, "");
}

/**
 * Установка признака наличия несохраненых изменений
 */
void MainForm::setChangeFlag() {
    if (!MenuItem_GetEnabled(miSave)) { //проверка наличия несхраненых уименений
        MenuItem_SetEnabled(miSave, TRUE); //включение кнопки сохранить (признак наличия несохраненых изменений)
        Form_SetCaption(form, (std::string(Form_GetCaption(form)) + "*").c_str()); //добавление признака в заголовок программы
    }
}

/**
 * Событие при закрытии формы
 * @param sender Объект вызвавший событие
 * @param canClose Флаг разрещающий хакрытие
 */
void MainForm::formCloseQuery(TObject sender, BOOL *canClose) {
	if (!checkChangeData()){   //проверка наличия несохраненых изменений
		*canClose = FALSE;                                             //отмера закрытия
		return;
	}
	if (countRes != 0) {
		for (int i=0; i < countRes; i++) {
			Label_Free(labelRes[i]);
			StringGrid_Free(tableRes[i]);
		}
		delete [] labelRes;
		delete [] tableRes;
		tableRes = nullptr;
		tableRes = nullptr;
		countRes = 0;
	}
}
void MainForm::st_formCloseQuery(TObject sender, BOOL *canClose) {
	TForm tform = (TForm)(sender);
	if (Form_GetTag(tform)) {
		MainForm* self = reinterpret_cast<MainForm*>(Form_GetTag(tform));
		self->formCloseQuery(sender, canClose);
	}
}

/**
 * Событие при изменении размера формы
 * @param sender Объект вызвавший событие
 */
void  MainForm::formResize(TObject sender) {
	//корректировка размера элементов
	StringGrid_SetWidth(capacityGrid, Form_GetClientWidth(form) - 16);
	StringGrid_SetWidth(numDoorsGrid, Form_GetClientWidth(form) - 16);
	StringGrid_SetWidth(coefQuanGrid, Form_GetClientWidth(form) - 16);
	ScrollBox_SetHeight(scrollBoxRes, Form_GetClientHeight(form) - 406);
	ScrollBox_SetWidth(scrollBoxRes, (Form_GetClientWidth(form) - 32) / 2);
	Image_SetWidth(chart, (Form_GetClientWidth(form) - 32) / 2);
	Image_SetLeft(chart, ScrollBox_GetWidth(scrollBoxRes) + 22);
	Image_SetHeight(chart, Form_GetClientHeight(form) - 456);
	Label_SetLeft(lChart, ScrollBox_GetWidth(scrollBoxRes) + 22);
	Button_SetLeft(bPrevChart, ScrollBox_GetWidth(scrollBoxRes) + 22);
	Button_SetTop(bPrevChart, Form_GetClientHeight(form) - 48);
	Button_SetTop(bNextChart, Form_GetClientHeight(form) - 48);\
	Button_SetLeft(bNextChart, Form_GetClientWidth(form) - 129);
	paintChart(numChart);
}
void MainForm::st_formResize(TObject sender) {
	TForm tform = (TForm)(sender);
	if (Form_GetTag(tform)) {
		MainForm* self = reinterpret_cast<MainForm*>(Form_GetTag(tform));
		self->formResize(sender);
	}
}


/**
 * Нажатие на подпункт "Создать"
 * @param sender Объект вызвавший событие
 */
void MainForm::miCreateClick(TObject sender) {
	if (!checkChangeData()) //проверка наличия несохраненных изменений
		return;
	Picture_Assign(Image_GetPicture(chart), NULL);//удаление старых результатов обработки
	numChart = 0;
	if (countRes != 0) {
		for (int i=0; i < countRes; i++) {
			Label_Free(labelRes[i]);
			StringGrid_Free(tableRes[i]);
		}
		delete [] labelRes;
		delete [] tableRes;
		tableRes = nullptr;
		tableRes = nullptr;
		countRes = 0;
	}
	MenuItem_SetEnabled(miSave, FALSE);
	MenuItem_SetEnabled(miDelCapacity, FALSE);
	MenuItem_SetEnabled(miDelNumDoors, FALSE);
	MenuItem_SetEnabled(miDelCoefQuan, FALSE);
	Button_SetEnabled(bPrevChart, FALSE);
	Button_SetEnabled(bNextChart, FALSE);
	Form_SetCaption(form, (std::string(Application_GetTitle(Application)) + " - " + DefFileName).c_str());
	StringGrid_SetColCount(capacityGrid, 2); //установка начальных состояни таблиц
	StringGrid_SetCells(capacityGrid, 1, 1, "");
	StringGrid_SetColCount(numDoorsGrid, 2);
	StringGrid_SetCells(numDoorsGrid, 1, 1, "");
	StringGrid_SetColCount(coefQuanGrid, 2);
	StringGrid_SetCells(coefQuanGrid, 1, 1, "");
	Edit_SetText(eTimeE, ""); //установка начальных состояни полей ввода
	Edit_SetText(eMinInterval, "");
	Label_SetCaption(lChart, "");
}
void MainForm::st_miCreateClick(TObject sender) {
	TMenuItem menuItem = (TMenuItem)(sender);
	if (MenuItem_GetTag(menuItem)) {
		MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
		self->miCreateClick(sender);
	}
}

/**
 * Нажатие на подпункт "Окрыть"
 * @param sender Объект вызвавший событие
 */
void MainForm::miOpenClick(TObject sender) {
	if (!checkChangeData()) //проверка наличия несохраненых изменений
		return;
	if (!OpenDialog_Execute(openDialog))     //вызов диалога открытия
		return;
	unsigned int CountByte;
	std::fstream file;
	file.open(convert_to_wstring_cpp(OpenDialog_GetFileName(openDialog)).c_str(), std::ios::in | std::ios::binary);              //открытие файла
	if (!file) {
		Application_MessageBox(Application, (std::string("Не удалось открыть файл \"") + OpenDialog_GetFileName(openDialog) + "\"!").c_str(),
							Application_GetTitle(Application), MB_OK | MB_ICONERROR);//если не удалось открыть файл
		return;
	}
	file.read((char*)&CountByte, sizeof(CountByte));   //чтение размера файла при записи
	file.seekg(0, std::ios::end);                          //установка указателя в конец файла
	file.clear();
	if (CountByte != file.tellg()){                   //проверка на целостность файла
		file.close();
		Application_MessageBox(Application, (std::string("Не удалось загрузить данные из файла \"") + OpenDialog_GetFileName(openDialog) + "\"!").c_str(),
							Application_GetTitle(Application), MB_OK | MB_ICONERROR); //вывод текста ошибки в модальное окно
		return;
	}
	file.clear();
	file.seekg(sizeof(CountByte));      //установка указателя после размера файла
	int colCount1, colCount2, colCount3;
	file.read((char*)&colCount1, sizeof(colCount1));//чтение размера таблицы 1
	file.read((char*)&colCount2, sizeof(colCount2));//чтение размера таблицы 1
	file.read((char*)&colCount3, sizeof(colCount3));//чтение размера таблицы 1
	int* dCapacityGrid = nullptr;
	int* dNumDoorsGrid = nullptr;
	double* dCoefQuanGrid = nullptr;
	try {
		dCapacityGrid = new int[colCount1];
		dNumDoorsGrid = new int[colCount2];
		dCoefQuanGrid = new double[colCount3];
	}
	catch (...) { //обработка исключений
		//освобождение памяти из-под массива
		delete[] dCapacityGrid;
		delete[] dNumDoorsGrid;
		delete[] dCoefQuanGrid;
		Application_MessageBox(Application, "Не хватает оперативной памяти для загрузки данных", Application_GetTitle(Application), MB_OK | MB_ICONERROR);
		return;
	}
	file.read((char*)&dCapacityGrid[0], sizeof(dCapacityGrid[0]) * colCount1);        //чтение данных таблицы 1
	StringGrid_SetColCount(capacityGrid, colCount1 + 1);                                             //установка размера таблицы 1
	for (int i=0; i < colCount1; i++) {                                             //запись данных таблицы 1
		StringGrid_SetCells(capacityGrid, i + 1, 0, std::to_string(i + 1).c_str());
		if (dCapacityGrid[i] == INT_MIN) {
			StringGrid_SetCells(capacityGrid, i + 1, 1, "");
		}
		else {
			StringGrid_SetCells(capacityGrid, i + 1, 1, std::to_string(dCapacityGrid[i]).c_str());
		}
	}
	delete [] dCapacityGrid;                                                        //освобождение данных из-под массива
	file.read((char*)&dNumDoorsGrid[0], sizeof(dNumDoorsGrid[0]) * colCount2);       //чтение данных таблицы 2
	StringGrid_SetColCount(numDoorsGrid, colCount2 + 1);                                            //установка размера таблицы 2
	for (int i=0; i < colCount2; i++) {                                            //запись данных таблицы 2
		StringGrid_SetCells(numDoorsGrid, i + 1, 0, std::to_string(i + 1).c_str());
		if (dNumDoorsGrid[i] == INT_MIN) {
			StringGrid_SetCells(numDoorsGrid, i + 1, 1, "");
		}
		else {
			StringGrid_SetCells(numDoorsGrid, i + 1, 1, std::to_string(dNumDoorsGrid[i]).c_str());
		}
	}
	delete [] dNumDoorsGrid;                                                     //освобождение данных из-под массива
	file.read((char*)&dCoefQuanGrid[0], sizeof(dCoefQuanGrid[0]) * colCount3);     //чтение данных таблицы 3
	StringGrid_SetColCount(coefQuanGrid, colCount3 + 1);                                          //установка размера таблицы 3
	for (int i=0; i < colCount3; i++) {                                          //запись данных таблицы 3
		StringGrid_SetCells(coefQuanGrid, i + 1, 0, std::to_string(i + 1).c_str());
		if (dCoefQuanGrid[i] == DBL_MIN) {
			StringGrid_SetCells(coefQuanGrid, i + 1, 1, "");
		}
		else {
			StringGrid_SetCells(coefQuanGrid, i + 1, 1, std::to_string(dCoefQuanGrid[i]).c_str());
		}
	}
	delete [] dCoefQuanGrid;                                                       //освобождение данных из-под массива
	double dataEdit;
	file.read((char*)&dataEdit, sizeof(dataEdit));                                //чтение данных поля ввода 1
	if (dataEdit == DBL_MIN) {
		//запись данных в поле ввода 1
		Edit_SetText(eTimeE, "");
	}
	else {
		Edit_SetText(eTimeE, std::to_string(dataEdit).c_str());
	}
	file.read((char*)&dataEdit, sizeof(dataEdit));                                 //чтение данных поля ввода 2
	file.close();                                                                  //закрытие файла
	if (dataEdit == DBL_MIN) {
		//запись данных в поле ввода 2
		Edit_SetText(eMinInterval, "");
	}
	else {
		Edit_SetText(eMinInterval, std::to_string(dataEdit).c_str());
	}
	//очистка результатов
	//отключение (включение) кнопок удаления столбцов
	if (StringGrid_GetColCount(capacityGrid) > 2) {
		MenuItem_SetEnabled(miDelCapacity, true);
	}
	else {
		MenuItem_SetEnabled(miDelCapacity, false);
	}
	if (StringGrid_GetColCount(numDoorsGrid) > 2) {
		MenuItem_SetEnabled(miDelNumDoors, true);
	}
	else {
		MenuItem_SetEnabled(miDelNumDoors, false);
	}
	if (StringGrid_GetColCount(coefQuanGrid) > 2) {
		MenuItem_SetEnabled(miDelCoefQuan, true);
	}
	else {
		MenuItem_SetEnabled(miDelCoefQuan, false);
	}
	SaveDialog_SetFileName(saveDialog, OpenDialog_GetFileName(openDialog));                           //сохранение имени файла
	MenuItem_SetEnabled(miSave, false);                           //выключение кнопки сохранить (признак наличия несохраненных изменений)
	Form_SetCaption(form, (std::string(Application_GetTitle(Application)) + " - " + extractFileName(SaveDialog_GetFileName(saveDialog))).c_str()); //запись имени файла в заголовок
	Picture_Assign(Image_GetPicture(chart), NULL); //удаление старых результатов обработки
	if (countRes != 0) {
		for (int i=0; i < countRes; i++) {
			Label_Free(labelRes[i]);
			StringGrid_Free(tableRes[i]);
		}
		delete [] labelRes;
		delete [] tableRes;
		tableRes = nullptr;
		tableRes = nullptr;
		countRes = 0;
	}
	Button_SetEnabled(bPrevChart, FALSE);
	Button_SetEnabled(bNextChart, FALSE);
}
void MainForm::st_miOpenClick(TObject sender) {
	TMenuItem menuItem = (TMenuItem)(sender);
	if (MenuItem_GetTag(menuItem)) {
		MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
		self->miOpenClick(sender);
	}
}

/**
 * Нажатие на подпункт "Сохранить"
 * @param sender Объект вызвавший событие
 */
void MainForm::miSaveClick(TObject sender) {
	if (!checkSourData(true))                         //проверка данных для сохранения
		return;
	std::string oldFN = SaveDialog_GetFileName(saveDialog);          //сохранение старого имени файла
	if (std::string(SaveDialog_GetFileName(saveDialog)) == "") {            //если файл не открыт
		SaveDialog_SetFileName(saveDialog, DefFileName);         //запись начального имени файла
		if (!SaveDialog_Execute(saveDialog)) {             //вызов диалога сохранения
			SaveDialog_SetFileName(saveDialog, oldFN.c_str());           //возвращение старого имени файла
			return;
		}
	}
	if (!saveSourData()) {                              //сохранение данных
		SaveDialog_SetFileName(saveDialog, oldFN.c_str());               //возвращение старого имени файла
		return;
	}
	MenuItem_SetEnabled(miSave, FALSE);              //выключение кнопки сохранить (признак наличия несохраненых изменений)
	Form_SetCaption(form, (std::string(Application_GetTitle(Application)) + " - " + extractFileName(SaveDialog_GetFileName(saveDialog))).c_str()); //запись имени файла в заголовок
}
void MainForm::st_miSaveClick(TObject sender) {
	TMenuItem menuItem = (TMenuItem)(sender);
	if (MenuItem_GetTag(menuItem)) {
		MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
		self->miSaveClick(sender);
	}
}

/**
 * Нажатие на подпункт "Сохранить как"
 * @param sender Объект вызвавший событие
 */
void MainForm::miSaveAsClick(TObject sender) {
	if (!checkSourData(true))                         //проверка данных для сохранения
		return;
	std::string oldFN = SaveDialog_GetFileName(saveDialog);          //сохранение старого имени файла
	SaveDialog_SetFileName(saveDialog, DefFileName);         //запись начального имени файла
	if (!SaveDialog_Execute(saveDialog)) {             //вызов диалога сохранения
		SaveDialog_SetFileName(saveDialog, oldFN.c_str());           //возвращение старого имени файла
		return;
	}
	if (!saveSourData()) {                              //сохранение данных
		SaveDialog_SetFileName(saveDialog, oldFN.c_str());               //возвращение старого имени файла
		return;
	}
	MenuItem_SetEnabled(miSave, FALSE);              //выключение кнопки сохранить (признак наличия несохраненых изменений)
	Form_SetCaption(form, (std::string(Application_GetTitle(Application)) + " - " + extractFileName(SaveDialog_GetFileName(saveDialog))).c_str()); //запись имени файла в заголовок
}
void MainForm::st_miSaveAsClick(TObject sender) {
	TMenuItem menuItem = (TMenuItem)(sender);
	if (MenuItem_GetTag(menuItem)) {
		MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
		self->miSaveAsClick(sender);
	}
}

/**
 * Нажатие на подпункт "Выход"
 * @param sender Объект вызвавший событие
 */
void MainForm::miCloseClick(TObject sender) {
	Form_Close(form);
}
void MainForm::st_miCloseClick(TObject sender) {
	TMenuItem menuItem = (TMenuItem)(sender);
	if (MenuItem_GetTag(menuItem)) {
		MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
		self->miCloseClick(sender);
	}
}

/**
 * Добавление столбца в таблицу
 * @param grid Таблица, в которую надо добавить
 * @param miDel Кнопка удаления столбца этой таблицы
 */
void MainForm::addCol(TStringGrid* grid, TMenuItem* miDel) {
    StringGrid_SetColCount(*grid, StringGrid_GetColCount(*grid) + 1); //добавление столбца
    StringGrid_SetCells(*grid, StringGrid_GetColCount(*grid) - 1,
                    0, std::to_string(StringGrid_GetColCount(*grid) - 1).c_str()); //запись подписи дабавленого столбца
    StringGrid_SetCells(*grid, StringGrid_GetColCount(*grid) - 1,
                    1, ""); //очистка добавленой ячейки
    MenuItem_SetEnabled(*miDel, TRUE); //включение кнопки удаления столбцах
    setChangeFlag();
}

/**
 * Удаление столбца в таблицу
 * @param grid Таблица, в которую надо добавить
 * @param miDel Кнопка удаления столбца этой таблицы
 */
void MainForm::delCol(TStringGrid* grid, TMenuItem* miDel) {
    if (StringGrid_GetColCount(*grid) <= 2)  //проверка возможности удаления столбца
        return;
    StringGrid_SetColCount(*grid, StringGrid_GetColCount(*grid) - 1); //удаление столбца
    if (StringGrid_GetColCount(*grid) == 2)  //откючение кнопки удаления
        MenuItem_SetEnabled(*miDel, FALSE);
    setChangeFlag();
}

/**
 * Нажатие на подпункт "Добавить вместимость"
 * @param sender Объект вызвавший событие
 */
void MainForm::miAddCapacityClick(TObject sender) {
    addCol(&capacityGrid, &miDelCapacity);
}
void MainForm::st_miAddCapacityClick(TObject sender) {
    TMenuItem menuItem = (TMenuItem)(sender);
    if (MenuItem_GetTag(menuItem)) {
        MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
        self->miAddCapacityClick(sender);
    }
}
/**
 * Нажатие на подпункт "Удалить вместимость"
 * @param sender Объект вызвавший событие
 */
void MainForm::miDelCapacityClick(TObject sender) {
    delCol(&capacityGrid, &miDelCapacity);
}
void MainForm::st_miDelCapacityClick(TObject sender) {
    TMenuItem menuItem = (TMenuItem)(sender);
    if (MenuItem_GetTag(menuItem)) {
        MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
        self->miDelCapacityClick(sender);
    }
}
/**
 * Нажатие на подпункт "Добавить число дверей"
 * @param sender Объект вызвавший событие
 */
void MainForm::miAddNumDoorsClick(TObject sender) {
    addCol(&numDoorsGrid, &miDelNumDoors);
}
void MainForm::st_miAddNumDoorsClick(TObject sender) {
    TMenuItem menuItem = (TMenuItem)(sender);
    if (MenuItem_GetTag(menuItem)) {
        MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
        self->miAddNumDoorsClick(sender);
    }
}

/**
 * Нажатие на подпункт "Удалить число дверей"
 * @param sender Объект вызвавший событие
 */
void MainForm::miDelNumDoorsClick(TObject sender) {
    delCol(&numDoorsGrid, &miDelNumDoors);
}
void MainForm::st_miDelNumDoorsClick(TObject sender) {
    TMenuItem menuItem = (TMenuItem)(sender);
    if (MenuItem_GetTag(menuItem)) {
        MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
        self->miDelNumDoorsClick(sender);
    }
}

/**
 * Нажатие на подпункт "Добавить коэф. входа и выхода"
 * @param sender Объект вызвавший событие
 */
void MainForm::miAddCoefQuanClick(TObject sender) {
    addCol(&coefQuanGrid, &miDelCoefQuan);
}
void MainForm::st_miAddCoefQuanClick(TObject sender) {
    TMenuItem menuItem = (TMenuItem)(sender);
    if (MenuItem_GetTag(menuItem)) {
        MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
        self->miAddCoefQuanClick(sender);
    }
}

/**
 * Нажатие на подпункт "Удалить коэф. входа и выхода"
 * @param sender Объект вызвавший событие
 */
void MainForm::miDelCoefQuanClick(TObject sender) {
    delCol(&coefQuanGrid, &miDelCoefQuan);
}
void MainForm::st_miDelCoefQuanClick(TObject sender) {
    TMenuItem menuItem = (TMenuItem)(sender);
    if (MenuItem_GetTag(menuItem)) {
        MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
        self->miDelCoefQuanClick(sender);
    }
}

/**
 * Нажатие на кнопку "Обработать данные"
 * @param sender Объект вызвавший событие
 */
void MainForm::bCalcDataClick(TObject sender) {
	if (!checkSourData(false)) //проверка данных для обработки
		return;
	if (countRes != 0) { //удаление старых результатов обработки
		for (int i = 0; i < countRes; ++i) {
			StringGrid_Free(tableRes[i]);
			Label_Free(labelRes[i]);
		}
		delete [] tableRes;
		delete [] labelRes;
		tableRes = nullptr;
		labelRes = nullptr;
		countRes = 0;
	}
	//объявление массивов
	int* dCapacityGrid = nullptr;
	int* dNumDoorsGrid = nullptr;
	double* dCoefQuanGrid = nullptr;
	try {
		dCapacityGrid = new int[StringGrid_GetColCount(capacityGrid) - 1];
		dNumDoorsGrid = new int[StringGrid_GetColCount(numDoorsGrid) - 1];
		dCoefQuanGrid = new double[StringGrid_GetColCount(coefQuanGrid) - 1];
		tableRes = new TStringGrid[StringGrid_GetColCount(coefQuanGrid) - 1];
		labelRes = new TLabel[StringGrid_GetColCount(coefQuanGrid) - 1];
	}
	catch (...) { //обработка исключений
		//освобождение памяти из-под массива
		delete[] dCapacityGrid;
		delete[] dNumDoorsGrid;
		delete[] dCoefQuanGrid;
		delete[] tableRes;
		delete[] labelRes;
		Application_MessageBox(Application, "Не хватает оперативной памяти для обработки данных", Application_GetTitle(Application), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	countRes = StringGrid_GetColCount(coefQuanGrid) - 1;
	for (int i = 0; i < StringGrid_GetColCount(capacityGrid) - 1; ++i)            //считываение двнных для обработки
		dCapacityGrid[i] = std::stoi(StringGrid_GetCells(capacityGrid, i + 1, 1));
	for (int i = 0; i < StringGrid_GetColCount(numDoorsGrid) - 1; ++i)
		dNumDoorsGrid[i] = std::stoi(StringGrid_GetCells(numDoorsGrid, i + 1, 1));
	for (int i = 0; i < StringGrid_GetColCount(coefQuanGrid) - 1; ++i)
		dCoefQuanGrid[i] = std::stof(StringGrid_GetCells(coefQuanGrid, i + 1, 1));
	int tableTop = 5;
	//считывание полей ввода
	double timeIE = std::stof(Edit_GetText(eTimeE));
	double minInterval = std::stof(Edit_GetText(eMinInterval));
	for (int q = 0; q < StringGrid_GetColCount(coefQuanGrid) - 1; ++q) {
		labelRes[q] = Label_Create(scrollBoxRes); //создание подписи к таблице
		Label_SetParent(labelRes[q], scrollBoxRes);  //начальные настройки подписи
		Label_SetHeight(labelRes[q], 17);
		Label_SetTop(labelRes[q], tableTop);
		tableTop += 17;
		Label_SetLeft(labelRes[q], 5);
		Label_SetAlign(labelRes[q], alTop);
		Label_SetCaption(labelRes[q], (std::string("Коэффициент входящих и выходящих, Квв: ") +
														std::to_string(dCoefQuanGrid[q])).c_str());
		tableRes[q] = StringGrid_Create(scrollBoxRes);
		StringGrid_SetParent(tableRes[q], scrollBoxRes);
		StringGrid_SetColCount(tableRes[q], StringGrid_GetColCount(capacityGrid));
		StringGrid_SetOptions(tableRes[q], goThumbTracking);
		StringGrid_SetRowCount(tableRes[q], StringGrid_GetColCount(numDoorsGrid));
		StringGrid_SetHeight(tableRes[q], 73);
		StringGrid_SetTop(tableRes[q], tableTop);
		tableTop += 73;
		StringGrid_SetLeft(tableRes[q], 5);
		StringGrid_SetColWidths(tableRes[q], 0 , 75);
		StringGrid_SetAlign(tableRes[q], alTop);
		StringGrid_SetCells(tableRes[q], 0, 0, "Kдв\\\u03A9");
		fMax = DBL_MIN;
		for (int i = 0; i < StringGrid_GetColCount(capacityGrid) - 1; ++i) { //заполнение подписи столбцов
			StringGrid_SetCells(tableRes[q], i + 1, 0 , std::to_string(dCapacityGrid[i]).c_str());
		}
		for (int i = 0; i < StringGrid_GetColCount(numDoorsGrid) - 1; ++i) { //расчет данных
			double res = 0;
			StringGrid_SetCells(tableRes[q], 0, i + 1, std::to_string(dNumDoorsGrid[i]).c_str()); //заполнение подписи строк
			for (int j = 0; j < StringGrid_GetColCount(capacityGrid) - 1; ++j) {
				res = 2.56 * sqrt(minInterval) + (((double)dCapacityGrid[j] * dCoefQuanGrid[q] * timeIE)
							/ dNumDoorsGrid[i]) + 3; //расчет результата
				StringGrid_SetCells(tableRes[q], j + 1, i + 1, std::to_string(round(res * 100) / 100).c_str());
				if (fMax < res) { //поиск макстимального значения
					fMax = res;
				}
			}
		}
	}
	numChart = 0;
	Label_SetCaption(lChart, "");
	paintChart(numChart);
	Button_SetEnabled(bPrevChart, FALSE);
	Button_SetEnabled(bNextChart, true);
}
void MainForm::st_bCalcDataClick(TObject sender) {
	TButton button = (TButton)(sender);
	if (Button_GetTag(button)) {
		MainForm* self = reinterpret_cast<MainForm*>(Button_GetTag(button));
		self->bCalcDataClick(sender);
	}
}
void MainForm::st_miCalcDataClick(TObject sender) {
	TMenuItem menuItem = (TMenuItem)(sender);
	if (MenuItem_GetTag(menuItem)) {
		MainForm* self = reinterpret_cast<MainForm*>(MenuItem_GetTag(menuItem));
		self->bCalcDataClick(sender);
	}
}

/**
 * Нажатие на кнопку "Следующий график"
 * @param sender Объект вызвавший событие
 */
void MainForm::bNextChartClick(TObject sender) {
	Button_SetEnabled(bPrevChart, TRUE);                                          //включени кнопки предыдущий график
	numChart++;                                                        //изменение номера графика
	if (numChart == countRes - 1)                                   //выключение кнопки
		Button_SetEnabled(bNextChart, FALSE);
	paintChart(numChart);
}
void MainForm::st_bNextChartClick(TObject sender) {
	TButton button = (TButton)(sender);
	if (Button_GetTag(button)) {
		MainForm* self = reinterpret_cast<MainForm*>(Button_GetTag(button));
		self->bNextChartClick(sender);
	}
}

/**
 * Нажатие на кнопку "Предыдущий график"
 * @param sender Объект вызвавший событие
 */
void MainForm::bPrevChartClick(TObject sender) {
	numChart--;                                                    //изменение номера графика
	Button_SetEnabled(bNextChart, TRUE);                                  //включени кнопки следующий график
	if (numChart == 0)                                             //выключение кнопки
		Button_SetEnabled(bPrevChart, FALSE);
	paintChart(numChart);
}
void MainForm::st_bPrevChartClick(TObject sender) {
	TButton button = (TButton)(sender);
	if (Button_GetTag(button)) {
		MainForm* self = reinterpret_cast<MainForm*>(Button_GetTag(button));
		self->bPrevChartClick(sender);
	}
}

/**
 * Нажатие на кнопку клавиатуры при вводе целых чисел
 * @param sender Объект вызвавший событие
 * @param key Нажатая кнопка
 */
void MainForm::intGridKeyPress(TObject sender, Char* key) {
	setChangeFlag();
	if (!((*key >= '0' && *key <= '9') || (int)*key == 3 || (int)*key == 8 ||  (int)*key == 13 || (int)*key == 22 || (int)*key == 24 || (int)*key == 26)) {   //проверка на допустимость введенного символа
		StatusBar_SetSimpleText(statusBar, (std::string("Введен недопустимый символ \"") + (char)*key + "\"").c_str());//вывод сообщения в статус бар
		*key = 0;                                                                            //отмена ввода
		return;
	}
	StatusBar_SetSimpleText(statusBar, "");
}
void MainForm::st_intGridKeyPress(TObject sender, Char* key) {
	TStringGrid grid = (TStringGrid)(sender);
	if (StringGrid_GetTag(grid)) {
		MainForm* self = reinterpret_cast<MainForm*>(StringGrid_GetTag(grid));
		self->intGridKeyPress(sender, key);
	}
}

/**
 * Нажатие на кнопку клавиатуры при вводе вещественных чисел
 * @param sender Объект вызвавший событие
 * @param key Нажатая кнопка
 */
void MainForm::doubleKeyPress(TObject sender, Char* key) {
	setChangeFlag();
	if (!((*key >= '0' && *key <= '9') || (int)*key == 3 || (int)*key == 8 || (int)*key == 44 || (int)*key == 13 || (int)*key == 22 || (int)*key == 24 || (int)*key == 26)) {   //проверка на допустимость введенного символа
		StatusBar_SetSimpleText(statusBar, (std::string("Введен недопустимый символ \"") + (char)*key + "\"").c_str());//вывод сообщения в статус бар
		*key = 0;                                                                            //отмена ввода
		return;
	}
	StatusBar_SetSimpleText(statusBar, "");
}
void MainForm::st_gridDoubleKeyPress(TObject sender, Char* key) {
	TStringGrid grid = (TStringGrid)(sender);
	if (StringGrid_GetTag(grid)) {
		MainForm* self = reinterpret_cast<MainForm*>(StringGrid_GetTag(grid));
		self->doubleKeyPress(sender, key);
	}
}
void MainForm::st_editDoubleKeyPress(TObject sender, Char* key) {
	TEdit grid = (TEdit)(sender);
	if (Edit_GetTag(grid)) {
		MainForm* self = reinterpret_cast<MainForm*>(Edit_GetTag(grid));
		self->doubleKeyPress(sender, key);
	}
}


/**
 * Проверка данных на корректность и допустимость
 * @param forSave Флаг типа проверка (true - для сохранения)
 * @return true - Данные корректны и допустимы
 * @return false - Данные не корректны и не допустимы
 */
bool MainForm::checkSourData(bool forSave) {
	std::string errMess = "";                                //переменная для сообщения об ошибке
	for (int i = 1; i < StringGrid_GetColCount(capacityGrid); i++) {   //перебор значений 1 таблицы
		int testValue = 0;
		if (!(forSave && std::string(StringGrid_GetCells(capacityGrid, i, 1)) == "")
				&& !tryStrToInt(StringGrid_GetCells(capacityGrid, i, 1), testValue)
				|| testValue < 0) {  //проверка значений 1 таблицы
			if (errMess == "")     //формирование сообщения об ошибки
				errMess = std::string("Некорректные или недопустимые значения вместимости транспорта №: ") + std::to_string(i);
			else
				errMess += std::string(", ") + std::to_string(i);
		}
	}
	if (errMess != "")
		errMess += ". ";
	bool notErr = true;
	for (int i = 1; i < StringGrid_GetColCount(numDoorsGrid); i++) {     //перебор значений 2 таблицы
		int testValue = 0;
		if (!(forSave && std::string(StringGrid_GetCells(numDoorsGrid, i, 1)) == "")
			&& !tryStrToInt(StringGrid_GetCells(numDoorsGrid, i, 1), testValue)
			|| testValue < 0) {  //проверка значений 2 таблицы
			if (notErr) {          //формирование сообщения об ошибки
				notErr = false;
				errMess += std::string("Некорректные или недопустимые значения числа дверей №: ") + std::to_string(i);
			}
			else
				errMess += std::string(", ") + std::to_string(i);
		}
	}
	if (!notErr) {              //формирование сообщения об ошибки
		errMess += ". ";
		notErr = true;
	}
	for (int i =1; i < StringGrid_GetColCount(coefQuanGrid); i++) {     //перебор значений 3 таблицы
		float testValue = 0;
		if (!(forSave && std::string(StringGrid_GetCells(coefQuanGrid, i, 1)) == "")
			&& !tryStrToFloat(StringGrid_GetCells(coefQuanGrid, i, 1), testValue)
			|| testValue < 0) {     //проверка занчений 3 таблицы
			if (notErr) {          //формирование сообщения об ошибки
				notErr = false;
				errMess += std::string("Некорректные или недопустимые значения коэффициента выхода и входа №: ") + std::to_string(i);
			}
			else
				errMess += std::string(", ") + std::to_string(i);
		}
	}
	if (!notErr) {             //формирование сообщения об ошибки
		errMess += ". ";
		notErr = true;
	}
	float testValue = 0;
	if (!(forSave && std::string(Edit_GetText(eTimeE)) == "") && (!tryStrToFloat(Edit_GetText(eTimeE), testValue)
	                                                              || testValue < 0)) {   //проверка значения в 1 поле ввода
		notErr = false;
		errMess += "Некорректные или недопустимое значение: времени выхода и входа";  //формирование сообщения об ошибки
	}
	if (!(forSave && std::string(Edit_GetText(eMinInterval)) == "") && (!tryStrToFloat(Edit_GetText(eMinInterval), testValue)
	                                                       || testValue < 0)) {     //проверка значения в 2 поле ввода
		if (notErr) {                                                       //формирование сообщения об ошибки
			notErr = false;
			errMess += "Некорректные или недопустимое значение: минимального интервала.";
		}
		else
			errMess += ", минимального интервала.";
	}
	if (errMess != "") {                  //если были найдены ошибки
		StatusBar_SetSimpleText(statusBar, errMess.c_str()); //вывод теста ошибки в статус бар
		Application_MessageBox(Application, errMess.c_str(), Application_GetTitle(Application), MB_OK | MB_ICONEXCLAMATION);
		return false;        //завершение с ошибками
	}
	return true;            //завершение без ошибок
}

/**
 * Проверка наличия несохраненных изменений и выбор действия над ними
 * @return true - Продолжать действие можно
 * @return false - Продолжать действие нельзя
 */
bool MainForm::checkChangeData() {
	if (MenuItem_GetEnabled(miSave)) { //проверка наличия несохраненных изменений
		std::string oldFN = SaveDialog_GetFileName(saveDialog); //сохранение имени открытого файла
		if (oldFN == "") {
			oldFN = DefFileName; //запись дефолтного имени файла
		}
		switch (Application_MessageBox(Application, (std::string("Присутствуют не сохраненые изменения. Сохранить изменения в файле \"") +
			oldFN + "\"?").c_str(), Application_GetTitle(Application), MB_YESNOCANCEL | MB_ICONQUESTION)) {
			case mrCancel:                     //нажатие отмена
				return false;                  //выход с запретом дальнейших действий
			case mrNo:
				return true;                    //выход с разрешением дальнейших действий
			case mrYes:
				if (!checkSourData(true))                         //проверка данных для сохранения
					return false;
				if (std::string(SaveDialog_GetFileName(saveDialog)) == "") {            //если файл не открыт
					SaveDialog_SetFileName(saveDialog, DefFileName);         //запись начального имени файла
					if (!SaveDialog_Execute(saveDialog)) {             //вызов диалога сохранения
						SaveDialog_SetFileName(saveDialog, "");           //возвращение старого имени файла
						return false;                  //выход с запретом дальнейших действий
					}
					oldFN = "";
				}
				if (!saveSourData()) {                              //сохранение данных
					SaveDialog_SetFileName(saveDialog, oldFN.c_str());                //возвращение старого имени файла
					return false;                  //выход с запретом дальнейших действий
				}
				break;
			default:
				break;
		}
	}
	return true;      //выход с разрешением дальнейших действий
}

std::wstring MainForm::convert_to_wstring_cpp(const char* str) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);
}

/**
 * Сохранение исходных данных в файл
 * @return true - сохранение прошло успешно
 * @return false - не удалось сохранить
 */
bool MainForm::saveSourData() {
	//Объявление массивов
	int* dCapacityGrid = nullptr;
	int* dNumDoorsGrid = nullptr;
	double* dCoefQuanGrid = nullptr;
	try {
		dCapacityGrid = new int[StringGrid_GetColCount(capacityGrid) - 1];
		dNumDoorsGrid = new int[StringGrid_GetColCount(numDoorsGrid) - 1];
		dCoefQuanGrid = new double[StringGrid_GetColCount(coefQuanGrid) - 1];
	}
	catch (...) { //обработка исключений
		//освобождение памяти из-под массива
		delete[] dCapacityGrid;
		delete[] dNumDoorsGrid;
		delete[] dCoefQuanGrid;
		Application_MessageBox(Application, "Не хватает оперативной памяти для обработки данных", Application_GetTitle(Application), MB_OK | MB_ICONERROR);
		return false;
	}
	for (int i = 0; i < StringGrid_GetColCount(capacityGrid) - 1; ++i) { //запись данных из 1 таблице в массив
		if (std::string(StringGrid_GetCells(capacityGrid, i + 1, 1)) == "") {
			dCapacityGrid[i] = INT_MIN; //если ячейка пустая, то запись минимального значения
		}
		else {
			dCapacityGrid[i] = std::stoi(StringGrid_GetCells(capacityGrid, i + 1, 1));
		}
	}
	for (int i = 0; i < StringGrid_GetColCount(numDoorsGrid) - 1; ++i) { //запись данных из 2 таблице в массив
		if (std::string(StringGrid_GetCells(numDoorsGrid, i + 1, 1)) == "") {
			dNumDoorsGrid[i] = INT_MIN; //если ячейка пустая, то запись минимального значения
		}
		else {
			dNumDoorsGrid[i] = std::stoi(StringGrid_GetCells(numDoorsGrid, i + 1, 1));
		}
	}
	for (int i = 0; i < StringGrid_GetColCount(coefQuanGrid) - 1; ++i) { //запись данных из 3 таблице в массив
		if (std::string(StringGrid_GetCells(coefQuanGrid, i + 1, 1)) == "") {
			dCoefQuanGrid[i] = DBL_MIN; //если ячейка пустая, то запись минимального значения
		}
		else {
			dCoefQuanGrid[i] = std::stoi(StringGrid_GetCells(coefQuanGrid, i + 1, 1));
		}
	}
	double dataEdit;                    //инициализация вспомогательных элементов
	int colCount;
	unsigned int CountByte = sizeof(CountByte) + sizeof(colCount) * 3 + (StringGrid_GetColCount(capacityGrid) - 1) * sizeof(dCapacityGrid[0]) +  //посчет будущего размера файла для провеки целостности при чтении
							  (StringGrid_GetColCount(numDoorsGrid) - 1) * sizeof(dNumDoorsGrid[0])+ (StringGrid_GetColCount(coefQuanGrid) - 1) * sizeof(dCoefQuanGrid[0])+
								sizeof(dataEdit) * 2;
	std::ofstream file;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	file.open(convert_to_wstring_cpp(SaveDialog_GetFileName(saveDialog)).c_str(), std::ios::out | std::ios::binary);  //создание файла для сохранения
	if (!file) {                                 //если не удалось создать файл
		delete[] dCapacityGrid; //освобождение памяти из-под массива
		delete[] dNumDoorsGrid;
		delete[] dCoefQuanGrid;
		Application_MessageBox(Application, (std::string("Не удалось создать файл \"") + SaveDialog_GetFileName(saveDialog) + "\"!").c_str(),
							Application_GetTitle(Application), MB_OK | MB_ICONERROR);
		return false;      //завершение с ошибкой
	}
	file.write((char*)&CountByte, sizeof(CountByte)); //запись в файл размера файла
	colCount = StringGrid_GetColCount(capacityGrid) - 1;
	file.write((char*)&colCount, sizeof(colCount)); //запись в файл размера 1 таблицы
	colCount = StringGrid_GetColCount(numDoorsGrid) - 1;
	file.write((char*)&colCount, sizeof(colCount)); //запись в файл размера 2 таблицы
	colCount = StringGrid_GetColCount(coefQuanGrid) - 1;
	file.write((char*)&colCount, sizeof(colCount)); //запись в файл размера 3 таблицы
	file.write((char*)&dCapacityGrid[0], sizeof(dCapacityGrid[0]) * (StringGrid_GetColCount(capacityGrid) - 1));  //запись данных 1 таблицы
	delete [] dCapacityGrid;                                                  //освобождение памяти из-под 1 массива
	file.write((char*)&dNumDoorsGrid[0], sizeof(dNumDoorsGrid[0]) * (StringGrid_GetColCount(numDoorsGrid) - 1));  //запись данных 2 таблицы
	delete [] dNumDoorsGrid;                                                   //освобождение памяти из-под 2 массива
	file.write((char*)&dCoefQuanGrid[0], sizeof(dCoefQuanGrid[0]) * colCount);  //запись данных 3 таблицы
	delete [] dCoefQuanGrid;                                                   //освобождение памяти из-под 3 массива
	if (std::string(Edit_GetText(eTimeE)) == "")                         //запись данных 1 поля ввода
		dataEdit = DBL_MIN;
	else
		dataEdit = std::atof(Edit_GetText(eTimeE));
	file.write((char*)&dataEdit, sizeof(dataEdit));
	if (std::string(Edit_GetText(eMinInterval)) == "")                   //запись данных 2 поля ввода
		dataEdit = DBL_MIN;
	else
		dataEdit = std::atof(Edit_GetText(eMinInterval));
	file.write((char*)&dataEdit, sizeof(dataEdit));
	file.close();                                   //закрытие файла
	return true;       //завершение с ошибкой без ошибки
}

/**
 * Рисование графика
 * @param numChart Индекс графика
 * @return true - график отрисован
 * @return false - не отрисован
 */
bool MainForm::paintChart(int numChart) {
	if (countRes == 0) {
		return false;
	}
	Picture_Assign(Image_GetPicture(chart), NULL);
	PatBlt(Canvas_GetHandle(Image_GetCanvas(chart)), 0, 0, Image_GetWidth(chart), Image_GetHeight(chart), WHITENESS);
	double a = 0 * M_PI / 180, b = 252 * M_PI/180, c = 15 * M_PI / 180 ; //углы поворота оси координат
	double l1 = cos(a) * cos(c) - cos(b) * sin(a) * sin(c);   //переменные для проекции
	double l2 = -cos(a) * sin(c) + cos(b) * sin(a) * cos(c);
	double l3 = sin(b) * sin(a);
	double m1 = sin(a) * cos(c) + cos(b) * cos(a) * sin(c);
	double m2 = -sin(a) * sin(c) + cos(b) * cos(a) * cos(c);
	double m3 = -sin(b) * cos(a);
	int oMax = INT_MIN;
	int kMax = INT_MIN;
	for (int i = 1; i < StringGrid_GetColCount(tableRes[numChart]); i++) {
		//поиск максимальных элементов
		if (oMax < std::atoi(StringGrid_GetCells(tableRes[numChart], i, 0))) {
			oMax = std::atoi(StringGrid_GetCells(tableRes[numChart], i, 0));
		}
	}
	for (int i = 1; i < StringGrid_GetRowCount(tableRes[numChart]); i++) {
		//поиск максимальных элементов
		if (kMax < std::atoi(StringGrid_GetCells(tableRes[numChart], 0, i))) {
			kMax = std::atoi(StringGrid_GetCells(tableRes[numChart], 0, i));
		}
	}
	kMax *= 5;
	double coefX = (Image_GetWidth(chart) - 20) / (oMax + kMax / 2);     //коэффициенты маштаба для расчета координат
	double coefY = (Image_GetHeight(chart) - 20)/(fMax + kMax / 2);
	double cordN = kMax / 2;                    //начало координат
	Pen_SetColor(Canvas_GetPen(Image_GetCanvas(chart)), (TColor)RGB(0, 0, 0));
	Pen_SetWidth(Canvas_GetPen(Image_GetCanvas(chart)), 1);
	int h = Image_GetHeight(chart);
	Canvas_MoveTo(Image_GetCanvas(chart), 10 + (cordN) * coefX,h - (10 + (cordN) * coefY));
	Canvas_LineTo(Image_GetCanvas(chart), 10 + (cordN + oMax * l1) * coefX,h - (10 + (cordN + m1 * oMax) * coefY));
	Canvas_MoveTo(Image_GetCanvas(chart), 10 + (cordN) * coefX,h - (10 + (cordN) * coefY));
	Canvas_LineTo(Image_GetCanvas(chart), 10 + (cordN + kMax * l2) * coefX,h - (10 + (cordN + m2 * kMax) * coefY));
	Canvas_MoveTo(Image_GetCanvas(chart), 10 + (cordN) * coefX,h - (10 + (cordN) * coefY));
	Canvas_LineTo(Image_GetCanvas(chart), 10 + (cordN + fMax * l3) * coefX,h - (10 + (cordN + m3 * fMax) * coefY));
	Pen_SetColor(Canvas_GetPen(Image_GetCanvas(chart)), (TColor)RGB(255, 0, 0));
	Label_SetCaption(lChart, Label_GetCaption(labelRes[numChart]));
	for (int i=1; i <  StringGrid_GetColCount(tableRes[numChart]); i++) {                      //Рисование графика
		Canvas_MoveTo(Image_GetCanvas(chart), 10 + (cordN + std::atoi(StringGrid_GetCells(tableRes[numChart], i, 0)) *
						l1 + std::atoi(StringGrid_GetCells(tableRes[numChart], 0, 1)) * 5 * l2 +
						std::atoi(StringGrid_GetCells(tableRes[numChart], i, 1)) * l3) * coefX,
						h - (10 + (cordN + std::atoi(StringGrid_GetCells(tableRes[numChart], i, 0)) * m1 +
						std::atoi(StringGrid_GetCells(tableRes[numChart], 0, 1)) * 5 * m2 +
						std::atoi(StringGrid_GetCells(tableRes[numChart], i, 1)) * m3) * coefY));
		for (int j = 2;j < StringGrid_GetRowCount(tableRes[numChart]); j++) {
			Canvas_LineTo(Image_GetCanvas(chart), 10 + (cordN + std::atoi(StringGrid_GetCells(tableRes[numChart], i, 0)) *
						l1 + std::atoi(StringGrid_GetCells(tableRes[numChart], 0, j)) * 5 * l2 +
						std::atoi(StringGrid_GetCells(tableRes[numChart], i, j)) * l3) * coefX,
						h - (10 + (cordN + std::atoi(StringGrid_GetCells(tableRes[numChart], i, 0)) *
							m1 + std::atoi(StringGrid_GetCells(tableRes[numChart], 0, j)) * 5 * m2 +
							std::atoi(StringGrid_GetCells(tableRes[numChart], i, j)) * m3) * coefY));
		}
	}
	for (int i=1; i < StringGrid_GetRowCount(tableRes[numChart]); i++) {                      //Рисование графика
		Canvas_MoveTo(Image_GetCanvas(chart), 10 + (cordN + std::atoi(StringGrid_GetCells(tableRes[numChart], 1, 0)) *
					l1 + std::atoi(StringGrid_GetCells(tableRes[numChart], 0, i)) * 5 * l2 + std::atoi(StringGrid_GetCells(tableRes[numChart], 1, i)) *
					l3) * coefX,h - (10 + (cordN + std::atoi(StringGrid_GetCells(tableRes[numChart], 1, 0)) *
						m1 + std::atoi(StringGrid_GetCells(tableRes[numChart], 0, i)) * 5 * m2 + std::atoi(StringGrid_GetCells(tableRes[numChart], 1, i)) *
						m3) * coefY));
		for (int j = 2;j < StringGrid_GetColCount(tableRes[numChart]); j++) {
			Canvas_LineTo(Image_GetCanvas(chart), 10 + (cordN + std::atoi(StringGrid_GetCells(tableRes[numChart], j, 0)) *
				l1 + std::atoi(StringGrid_GetCells(tableRes[numChart], 0, i)) * 5 * l2 + std::atoi(StringGrid_GetCells(tableRes[numChart], j, i)) *
				l3) * coefX,h - (10 + (cordN + std::atoi(StringGrid_GetCells(tableRes[numChart], j, 0)) * m1 +
					std::atoi(StringGrid_GetCells(tableRes[numChart], 0, i)) * 5 * m2 + std::atoi(StringGrid_GetCells(tableRes[numChart], j, i)) *
					m3) * coefY));
		}
	}
	return true;
}

std::string MainForm::extractFileName(const std::string& path) {
#ifdef _WIN32
	const char PATH_SEPARATOR = '\\';
#else
	const char PATH_SEPARATOR = '/';
#endif
	auto pos = path.rfind(PATH_SEPARATOR);
	return (pos == std::string::npos) ? path : path.substr(pos + 1);
}