from PySide2.QtWidgets import QApplication, QMessageBox
from PySide2.QtUiTools import QUiLoader
from PySide2.QtCore import QEventLoop, QTimer
from PySide2 import QtCore
from PySide2 import QtGui
import matplotlib.pyplot as plt
import pandas as pd
import serial
import datetime


class SI:
    mainPage = None
    aboutPage = None


# 重定向信号
class EmittingStr(QtCore.QObject):
    textWritten = QtCore.Signal(str)  # 定义一个发送str的信号，这里用的方法名与PyQt5不一样

    def write(self, text):
        self.textWritten.emit(str(text))
        loop = QEventLoop()
        QTimer.singleShot(30, loop.quit)
        loop.exec_()


def export():
    try:
        tmp = datetime.datetime.now()
        fileName = "%s-%s-%s-%s" % (tmp.month, tmp.day, tmp.hour, tmp.minute)
        listOfTempRop = []
        for idx, it1, it2 in zip(mainPage.x, mainPage.y_temp, mainPage.y_rop):
            listOfTempRop.append([idx, it1, it2])
        df = pd.DataFrame(listOfTempRop, columns=['time/s', 'Temperature/°C', 'Optical/Cd'])
        df.to_excel(fileName + ".xlsx", index=False)
    except Exception:
        print("导出错误")
    else:
        print("导出成功")


class aboutPage:
    def __init__(self):
        self.ui = QUiLoader().load('aboutPage.ui')


class mainPage:
    x = []
    y_temp = []
    y_rop = []

    def __init__(self):
        # 从文件中加载UI定义
        # 从 UI 定义中动态 创建一个相应的窗口对象
        # 注意：里面的控件对象也成为窗口对象的属性了
        # 比如 self.ui.button , self.ui.textEdit
        self.ui = QUiLoader().load('mainPage.ui')
        self.ui.actionAbout.triggered.connect(self.about)
        self.ui.actionExit.triggered.connect(self.exit)
        self.ui.buttonBegin.clicked.connect(self.collect)
        self.ui.buttonExport.clicked.connect(export)

        # # 下面将输出重定向到textEdit中
        import sys
        sys.stdout = EmittingStr()
        self.ui.edt_log.connect(sys.stdout, QtCore.SIGNAL("textWritten(QString)"), self.outputWritten)
        sys.stderr = EmittingStr()
        self.ui.edt_log.connect(sys.stderr, QtCore.SIGNAL("textWritten(QString)"), self.outputWritten)

    def outputWritten(self, text):
        # self.textEdit.clear()
        cursor = self.ui.edt_log.textCursor()
        cursor.movePosition(QtGui.QTextCursor.End)
        cursor.insertText(text)
        self.ui.edt_log.setTextCursor(cursor)
        self.ui.edt_log.ensureCursorVisible()

    def collect(self):
        time = int(self.ui.editTime.text().strip())
        port = self.ui.editPort.text().strip()
        baud = int(self.ui.editBaud.text().strip())

        # 波特率，标准值之一：50,75,110,134,150,200,300,600,1200,1800,2000,4800,9600,19200,38400,57600,115200
        # 超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
        timex = 5
        # 打开串口，并得到串口对象
        ser = serial.Serial(port, baud, timeout=timex)
        print("串口详情参数：", ser)

        print(ser.port)  # 获取到当前打开的串口名
        print(ser.baudrate)  # 获取波特率

        mainPage.x = []
        mainPage.y_temp = []
        mainPage.y_rop = []
        while len(mainPage.y_temp) < time:
            num = ser.in_waiting
            tmp = [0, 0, 0, 0, 0, 0, 0, 0]

            if num == 8:
                for i in range(num):
                    byte2Int = int(ser.read(1).hex(), 16)
                    # 转为十进制
                    if byte2Int > 9:
                        byte2Int = byte2Int - 87
                    print("rxd[%d]：" % (i) + str(byte2Int), end="\t")
                    tmp[i] = byte2Int
                    if i == num - 1:
                        print(' len: %d' % (len(mainPage.y_temp)))

            if num != 0:
                mainPage.x.append(len(mainPage.y_temp))
                mainPage.y_temp.append(tmp[2] * 16 + tmp[3] * 1)
                mainPage.y_rop.append(tmp[4] * 16 + tmp[5] * 1)

        print("-------------------------")
        ser.close()  # 关闭串口
        self.ui.editTime.setText("")

        plt.subplots_adjust(wspace=0.5, hspace=0)  # 调整子图间距
        fig1 = plt.subplot(121)
        plt.plot(mainPage.y_temp)
        plt.title('Temperature', fontsize=20)
        plt.xlabel('Time / s', fontsize=12)
        plt.ylabel('Temperature / °C', fontsize=12)
        fig2 = plt.subplot(122)
        plt.plot(mainPage.y_rop)
        plt.title('Optical', fontsize=20)
        plt.xlabel('Time / s', fontsize=12)
        plt.ylabel('Optical / Lux', fontsize=12)
        plt.show()

    def about(self):
        # self.ui.close()
        SI.aboutPage = aboutPage()
        SI.aboutPage.ui.show()

    def exit(self):
        self.ui.close()


app = QApplication([])
SI.mainPage = mainPage()
SI.mainPage.ui.show()
app.exec_()
# pyinstaller AppLcj.py --noconsole --hidden-import PySide2.QtXml