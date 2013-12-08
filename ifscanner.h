#ifndef _IF_SCANNER_H
#define _IF_SCANNER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#define __FAVOR_BSD
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <bits/ioctls.h>
#include <net/if.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <mutex>
#include <vector>
#include "iflog.h"
#include "concurent_queue.h"
#include <iostream>

struct Protocol  //TCP протокол
{
   int sock; //сокет
   int type_prot; //Тип протокола
   int head_on; //Заголовок пакета
   bool exit_thread; //выход из потока
   ConcurentQueue bufs; //очередь буфферов
   Buffer *indata; //доп. параметры callback функции
   ConcurentQueue outdata;  //вых. параметры callback функции
   functor proc; //сам функтор с callback функцией
   std::thread producer; //поток, который будет считывать с интерфэйса
   std::thread consumer; //поток, который обрабатывает буффер
   std::mutex queue_value; //синхронизация потоков
   Log *notelog; //лог уведомления
   Log *errlog; //лог ошибок
   
};

void producer_func (Protocol*); //функция чтения из сокета
void consumer_func (Protocol*); //функция обработки буферов

class InterfaceScanner //Основной класс
{
  public:
   InterfaceScanner(std::string,bool);  //Конструктор, 1 пармаетр: имя интерфэйса. 2 параметр:promiscuous mode
   int add_protocol (int); //Добавляем протокол. Если возратил -1, то ошибка
   int remove_protocol (size_t); //Удаляем протокол
   int set_callback (size_t,functor); //Устанавливаем функтор в протокол
   int set_max_buf (size_t,size_t);  //Максимальный размер очереди
   void set_max_log (size_t);
   void set_max_err_log (size_t);
   int set_input_data (size_t,Buffer*); //Задаем входные данные
   int launch_protocol (size_t);  //Запускаем протокол
   void launch_all ();  //Запускаем все протоколы
   int stop_protocol (size_t);  //Останавливаем протокол
   void stop_all(); //Останавливаем все протоколы
   std::vector<std::string> get_log(); //Получаем лог
   std::vector<std::string> get_error_log(); //Получаем лог ошибок
   int get_out_data(size_t,std::vector<Buffer*>&); //Получаем вых. данные из протокола
   ~InterfaceScanner();  //Деструктор, все чистим, все останавливаем
  private:
   ifreq ifopts;
   bool prom_mode;
   std::vector <Protocol*> prtcls;
   Log notelog;
   Log errlog;
};

#endif