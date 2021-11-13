#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <math.h>
#include <numeric>
#include "pbPlots.hpp"
#include "supportLib.hpp"

using namespace std;

const int BABA_STOCK = 250,
        BABA_PRICE = 180,
        WIZARD_STOCK = 250,
        WIZARD_PRICE = 180,
        ALI_STOCK = 100,
        ALI_PRICE = 225;

const float BABA_CHANGE = 0.01f,
            WIZARD_CHANGE = 0.001f,
            ALI_CHANGE = 0.f;

int main(){

    bool success;

    vector<double> wizardPrices,
                babaPrices,
                aliPrices;

    for (int i = 0; i < BABA_STOCK; i++){
        babaPrices.push_back(floor((i * BABA_CHANGE * BABA_PRICE) + BABA_PRICE));
    }

    for (int i = 0; i < WIZARD_STOCK; i++){
        wizardPrices.push_back(floor((i * WIZARD_CHANGE * WIZARD_PRICE) + WIZARD_PRICE));
    }

    for (int i = 0; i < ALI_STOCK; i++){
        aliPrices.push_back(floor((i * ALI_CHANGE * ALI_PRICE) + ALI_PRICE));
    }

    vector<double> babaStock(BABA_STOCK),
                    wizardStock(WIZARD_STOCK),
                    aliStock(ALI_STOCK);

    iota(begin(babaStock), end(babaStock), 1);
    iota(begin(wizardStock), end(wizardStock), 1);
    iota(begin(aliStock), end(aliStock), 1);


    StringReference *errorMessage = new StringReference();
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();



    ScatterPlotSeries *babaShop = GetDefaultScatterPlotSeriesSettings();
    babaShop->xs = &babaStock;
	babaShop->ys = &babaPrices;
	babaShop->linearInterpolation = true;
	babaShop->lineType = toVector(L"solid");
	babaShop->lineThickness = 2;
	babaShop->color = CreateRGBColor(0.5, 0, .5);

    ScatterPlotSeries *wizardGuildShop = GetDefaultScatterPlotSeriesSettings();
    wizardGuildShop->xs = &wizardStock;
	wizardGuildShop->ys = &wizardPrices;
	wizardGuildShop->linearInterpolation = true;
	wizardGuildShop->lineType = toVector(L"solid");
	wizardGuildShop->lineThickness = 2;
	wizardGuildShop->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSeries *aliShop = GetDefaultScatterPlotSeriesSettings();
    aliShop->xs = &aliStock;
	aliShop->ys = &aliPrices;
	aliShop->linearInterpolation = true;
	aliShop->lineType = toVector(L"solid");
	aliShop->lineThickness = 2;
	aliShop->color = CreateRGBColor(0, 1, 0);
    
    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 800;
	settings->height = 600;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
	settings->title = toVector(L"Nat Prices");
	settings->xLabel = toVector(L"Runes Bought");
	settings->yLabel = toVector(L"gp/rune");
	settings->scatterPlotSeries->push_back(babaShop);
    settings->scatterPlotSeries->push_back(wizardGuildShop);
    settings->scatterPlotSeries->push_back(aliShop);

    success = DrawScatterPlotFromSettings(imageRef, settings, errorMessage);

    if (success){
        vector<double> *pngData = ConvertToPNG(imageRef->image);
    WriteToFile(pngData, "plot.png");
    DeleteImage(imageRef->image);
    } else {
        cerr << "error";
    }

    return 0;
}