DIMRobotics Main Robot Firmware
============================

Этот репозиторий содержит исходный код проекта основного робота DIMRobotics сезона 2015.

Документация в wiki.

Руководство по установке, сборке и прошивке
===========================================

Установка
---------

0. Зависимости

        sudo apt-get install gcc gcc-avr avr-libc automake autoconf avrdude dfu-programmer

1. Устанавливаем Antares
        
        # тут ещё надо будет добавить установку kconfig-frontends

        cd /opt
        sudo chown `whoami` ./
        git clone https://github.com/nekromant/antares
        cd antares/abootstrap
        sudo make install

        cd ~
        echo "export ANTARES_INSTALL_DIR=/opt/antares" >> ~/.bashrc

        bash # перезапускаем bash, делаем видимой переменную окружения

2. Устанавливаем Cerebellum Library
        
        cd /opt
        git clone https://github.com/webconn/Cerebellum
        cd Cerebellum
        ./bootstrap.sh

3. Получаем исходники прошивки
        
        cd ~/robots # или куда хотим скачать прошивку
        git clone https://github.com/DIMRobotics/mainrobot-2015
        cd mainrobot-2015
        git checkout integral
        git pull

4. Собираем и прошивкаемся

        make build # сборка
        make deploy # прошивка

Процесс прошивки на Stepper-0.1
===============================

Для прошивки Stepper-0.1:

1. Нажимаем кнопку RESET, затем (не отпуская RESET) нажимаем BOOT, отпускаем RESET, отпускаем BOOT.
   Плата теперь в режиме прошивки

2. Подключаем USB.

3. make deploy

4. ???

5. PROFIT
