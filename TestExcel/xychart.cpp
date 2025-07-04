#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"

#include <QDebug>
#include <QDir>
#include <QFileInfo>

// Function to test creating a chart with separate X and Y ranges
int testXyChart() {
    qDebug() << "Creating Excel file with XY scatter chart...";

    // Create a new Excel file
    QXlsx::Document xlsx;
    QXlsx::Worksheet *sheet = xlsx.currentWorksheet();

    // Add some data for X and Y axes in separate columns
    // X values in column A
    sheet->write("A1", "X-Values");
    sheet->write("A2", 10);
    sheet->write("A3", 20);
    sheet->write("A4", 30);
    sheet->write("A5", 40);
    sheet->write("A6", 50);

    // Y values in column B
    sheet->write("B1", "Y-Values Series 1");
    sheet->write("B2", 15);
    sheet->write("B3", 25);
    sheet->write("B4", 32);
    sheet->write("B5", 48);
    sheet->write("B6", 55);

    // Y values for a second series in column C
    sheet->write("C1", "Y-Values Series 2");
    sheet->write("C2", 5);
    sheet->write("C3", 15);
    sheet->write("C4", 22);
    sheet->write("C5", 38);
    sheet->write("C6", 45);

    // Create a new chart
    QXlsx::Chart *scatterChart = sheet->insertChart(3, 3, QSize(300, 300));
    scatterChart->setChartType(QXlsx::Chart::CT_ScatterChart);
    scatterChart->setChartTitle("Scatter Chart with Separate X/Y Ranges");

    // Add the first data series using separate X and Y ranges
    // X from A2:A6, Y from B2:B6
    // For scatter charts, headerH usually refers to the header for Y values (series name)
    // and headerV is not typically used for scatter series data points themselves, but can be if data is structured that way.
    // Given our new addSeries(xRange, yRange, sheet, headerH, headerV),
    // headerH might take the header from yRange (e.g. B1 for yRange B2:B6)
    // headerV might take the header from xRange (e.g. A1 for xRange A2:A6)
    // The current simple header logic in the new addSeries might need adjustment for scatter charts' typical header usage.
    // Let's test with headerH=true (for Y series name) and headerV=false.
    QXlsx::CellRange xRange1("A2:A6");
    QXlsx::CellRange yRange1("B2:B6");
    // The headerH flag in addSeries(range, sheet, headerH, headerV) was for column-based series, taking header from range.firstRow().
    // The headerV flag was for row-based series, taking header from range.firstColumn().
    // My new addSeries(xRange, yRange, sheet, headerH, headerV) has a simplified header logic.
    // Let's assume headerH applies to yRange (to get "Y-Values Series 1" from B1)
    // and headerV applies to xRange (to get "X-Values" from A1) - though this is not standard for scatter series name.
    // Series name is usually from the Y-column header.
    // Let's try headerH = true to pick up B1, and headerV = false.
    scatterChart->addSeries(xRange1, yRange1, sheet, true, false);


    // Add the second data series using the same X range and Y from C2:C6
    QXlsx::CellRange yRange2("C2:C6");
    // headerH = true to pick up C1 as series name.
    scatterChart->addSeries(xRange1, yRange2, sheet, true, false);


    // Set axis titles
    scatterChart->setAxisTitle(QXlsx::Chart::Bottom, "Custom X-Axis Label");
    scatterChart->setAxisTitle(QXlsx::Chart::Left, "Custom Y-Axis Label");

    // Enable gridlines
    scatterChart->setGridlinesEnable(true, false); // Major gridlines true, minor false

    // Save the Excel file
    QString filePath = "TestXyChart.xlsx";
    if (xlsx.saveAs(filePath)) {
        qDebug() << "Excel file created successfully:" << QDir::current().absoluteFilePath(filePath);
        return 0; // Success
    } else {
        qDebug() << "Failed to create Excel file.";
        return -1; // Failure
    }
}
