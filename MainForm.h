#pragma once

#ifndef CALCBUSSTOPOCCUPLCL_MAINFORM_H
#define CALCBUSSTOPOCCUPLCL_MAINFORM_H


#include "libs/liblcl/liblcl.h"

#include <string>

#define DefFileName "Безымянный"

class MainForm {
public:
    MainForm() = default;
    ~MainForm() = default;
    void createForm();
    bool tryStrToInt(const std::string& str, int& outValue);
    bool tryStrToFloat(const std::string& str, float& outValue);
private:
    void createMenu();
    void createStatusBar();
    void createButtons();
    void createLabels();
    void createEdits();
    void createStringGrids();
    void createScrollBox();
    void createChart();
    void createDialogs();

    void setChangeFlag();

    void formCloseQuery(TObject sender, BOOL *canClose);
    static void st_formCloseQuery(TObject sender, BOOL *canClose);
    void formResize(TObject sender);
    static void st_formResize(TObject sender);


    void miCreateClick(TObject sender);
    static void st_miCreateClick(TObject sender);
    void miOpenClick(TObject sender);
    static void st_miOpenClick(TObject sender);
    void miSaveClick(TObject sender);
    static void st_miSaveClick(TObject sender);
    void miSaveAsClick(TObject sender);
    static void st_miSaveAsClick(TObject sender);
    void miCloseClick(TObject sender);
    static void st_miCloseClick(TObject sender);

    void addCol(TStringGrid* grid, TMenuItem* miDel);
    void delCol(TStringGrid* grid, TMenuItem* miDel);
    void miAddCapacityClick(TObject sender);
    static void st_miAddCapacityClick(TObject sender);
    void miDelCapacityClick(TObject sender);
    static void st_miDelCapacityClick(TObject sender);
    void miAddNumDoorsClick(TObject sender);
    static void st_miAddNumDoorsClick(TObject sender);
    void miDelNumDoorsClick(TObject sender);
    static void st_miDelNumDoorsClick(TObject sender);
    void miAddCoefQuanClick(TObject sender);
    static void st_miAddCoefQuanClick(TObject sender);
    void miDelCoefQuanClick(TObject sender);
    static void st_miDelCoefQuanClick(TObject sender);

    void bCalcDataClick(TObject sender);
    static void st_bCalcDataClick(TObject sender);
    static void st_miCalcDataClick(TObject sender);
    void bNextChartClick(TObject sender);
    static void st_bNextChartClick(TObject sender);
    void bPrevChartClick(TObject sender);
    static void st_bPrevChartClick(TObject sender);

    void intGridKeyPress(TObject sender, Char* key);
    static void st_intGridKeyPress(TObject sender, Char* key);

    void doubleKeyPress(TObject sender, Char* key);
    static void st_gridDoubleKeyPress(TObject sender, Char* key);
    static void st_editDoubleKeyPress(TObject sender, Char* key);

    bool checkSourData(bool forSave);
    bool checkChangeData();
    bool saveSourData();
    bool paintChart(int numChart);

    std::string extractFileName(const std::string& path);
    std::wstring convert_to_wstring_cpp(const char* str);

    //Главная форма
    TForm form;

    //Пункты Меню
    TMainMenu mainMenu;

    //Пункт "Файл"
    TMenuItem miFile; //Пункт "Файл"
    TMenuItem miCreate; //Подпункт "Создать"
    TMenuItem miOpen; //Подпункт "Открыть"
    TMenuItem miSave; //Подпункт "Сохранить"
    TMenuItem miSaveAs; //Подпункт "Сохранить как"
    TMenuItem miExit; //Подпункт "Выход"
    //Разделительные полосы в меню
    TMenuItem miDivLineFile1;
    TMenuItem miDivLineFile2;
    //Пункт "Редактировать"
    TMenuItem miEdit; //Пункт "Редактировать"
    TMenuItem miAddCapacity; //Подпункт "Добавить вместимость"
    TMenuItem miDelCapacity; //Подпункт "Удалить вместимость"
    TMenuItem miAddNumDoors; //Подпункт "Добавить число дверей"
    TMenuItem miDelNumDoors; //Подпункт "Удалить число дверей"
    TMenuItem miAddCoefQuan; //Подпункт "Добавить коэф. входа и выхода"
    TMenuItem miDelCoefQuan; //Подпункт "Удалить коэф. входа и выхода"
    //Разделительные полосы в меню
    TMenuItem miDivLineEdit1;
    TMenuItem miDivLineEdit2;
    //Пункт "Результаты"
    TMenuItem miRes;
    TMenuItem miCalcData; //Подпункт "Обработать данные"


    //кнопки
    TButton bCalcData; //Кнопка "Обработать данные"
    TButton bNextChart; //Кнопка "Предыдущий график"
    TButton bPrevChart; //Кнопка "Следующий график"

    //Подписи
    TLabel lInitData; //Подпись исходных данных
    TLabel lCapGrid; //Подпись таблицы вместимости
    TLabel lNumDorsGrid; //подпись таблицы числа дверей
    TLabel lcoefQuanGrid; //Подпись таблицы коэффициентов
    TLabel lTimeE; //Подпись поля ввода времени входа и выхода
    TLabel lMinInt; //Подпись поля ввода минимального интервала
    TLabel lres; //Подпись таблицы результатов
    TLabel lChart; //Подпись графика

    //Поля ввода
    TEdit eTimeE; //Поле ввода времени входа и выхода
    TEdit eMinInterval; //Поле ввода минимального интервала

    //Таблицы
    TStringGrid capacityGrid; //Таблица вместимости
    TStringGrid numDoorsGrid; //Таблица числа дверей
    TStringGrid coefQuanGrid; //Таблица коэффициентов

    //Скрол бокс
    TScrollBox scrollBoxRes; //Таблицарезультатов

    TImage chart; //График

    TStatusBar statusBar; //Статус бар

    //Диалоги
    TSaveDialog saveDialog;
    TOpenDialog openDialog;

    TStringGrid* tableRes; //Таблицы с результатами
    TLabel* labelRes; //Подписи таблиц с результатами
    int countRes;
    double fMax;
    int numChart;
};


#endif //CALCBUSSTOPOCCUPLCL_MAINFORM_H