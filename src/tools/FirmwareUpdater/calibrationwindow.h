#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QLineEdit>
#include <QTimer>
#include <downloader.h>
#include "firmwareupdatercore.h"
#include <QTableWidgetItem>
#include <QProgressBar>
#include "customtreewidgetitem.h"

namespace Ui {
class CalibrationWindow;
}

class CalibrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalibrationWindow(FirmwareUpdaterCore *core, CustomTreeWidgetItem *item, QWidget *parent = 0);
    ~CalibrationWindow();

protected:
    void closeEvent(QCloseEvent *e);
    void setCalibBias();
    void resetCalibBias();
    void setCurrBias();
    void resetCurrBias();
    void autoAdjust();
    void setSerial();
    void saveToEeprom();
    void setOffset(int chan, int value);
    void setCalibration();

private:
    Ui::CalibrationWindow *ui;
    CustomTreeWidgetItem *item;
    FirmwareUpdaterCore *core;
    bool sliderPressed[6];
    unsigned int adc[6];
    unsigned int maxadc[6];
    unsigned int minadc[6];
    bool first_time;
    unsigned int offset[6];
    unsigned int amp_gain1[6];
    unsigned int amp_gain2[6];
    int ch[6];
    int calib_bias[6];
    int curr_bias[6];
    unsigned int matrix[3][6][6];
    unsigned int calib_matrix[6][6];
    unsigned int calibration_value;
    unsigned int calib_const[3];
    unsigned int full_scale_const[6];
    char serial_no[8];
    int selected;
    bool matrixA_changed;
    bool matrixB_changed;
    bool matrixC_changed;
    bool serial_number_changed;
    bool something_changed;
    bool eeprom_saved_status;
    QList<QSlider*>slider_gain;
    QTimer *timer;
    int bus;
    int id;
    QMutex mutex;
    QMutex sliderMutex;
    QProgressBar *progress;
    bool keepRunning;
private slots:
    void onTimeout();
    void onSliderZeroChanged(int);
    void onOffsetSliderValue(int);
    void onMatrixAChanged(QTableWidgetItem*);
    void onMatrixBChanged(QTableWidgetItem*);
    void onMatrixCChanged(QTableWidgetItem*);
    void onSerialChanged(QString);
    void onLoading(bool);
    void onSetText(QLineEdit*,QString text);
    void onSetText(QTableWidgetItem*,QString text);
    void onSliderValue(QSlider*, int value);
    void onSetCalibBias(bool click);
    void onResetCalibBias(bool click);
    void onSetCurrBias(bool click);
    void onResetCurrBias(bool click);
    void onAutoAdjust(bool click);
    void onSetSerial(bool click);
    void onSetSerialChanged(bool);
    void onResetCalibMatrix(bool);
    void onUseMatrixChanged(int);
    void onSetMatrix(int index);
    void onSaveToEeprom(bool click);
    void onSetCalibration(bool click);
    void resetMatricesState(int index = -1);
    void onUpdateTitle();
    void onSliderPressed();
    void onSliderReleased();
signals:
    void loading(bool = true);
    void setText(QLineEdit*,QString text);
    void setText(QTableWidgetItem*,QString text);
    void setSliderValue(QSlider*, int value);
    void setSerialChanged(bool);
    void setMatrix(int index);
    void resetMatrices(int index = -1);
    void updateTitle();



};

#endif // CALIBRATIONWINDOW_H
