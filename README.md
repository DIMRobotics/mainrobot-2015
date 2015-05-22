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
        git fetch

4. Собираем и прошиваемся

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

Добавление своих исходников
===========================

1. Создаём файл в дереве
        
        your-text-editor src/myfile.c

2. Добавляем его в Makefile, чтобы собрался

        echo "objects-y += myfile.o" >> src/Makefile # важно, что файл с .o, не .с

3. В файле пишем что-нибудь в этом роде

        #include <robot/extra.h>

        ANTARES_APP(my_strategy)
        {
                twist(2, 2, 200);

                paw_open();

                // ещё больше кода

                while (1) ;;; // ANTARES_APP циклит исполнение, так можно подвесить робота по окончанию работы
        }

4. Пересобираем
        
        make clean # только после первого дополнения файла в дерево, после изменений не нужно
        make build
        make deploy

5. Плохо работает? goto 3
