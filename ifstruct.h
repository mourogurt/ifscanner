#ifndef _IF_STRUCT_H
#define _IF_STRUCT_H

struct Buffer;

typedef int (*PROTOCOL_CALLBACK)(Buffer *, Buffer *, Buffer *);  //callback функция протокола 1 арг - буффер; 2 арг. - входные данные
                                                                   //3 арг. - выходные данные. Если возвр. знач. отлично от 0, то сген. ошибка


struct Buffer  //Буффер объект
{
   char* buff; //буфер
   unsigned int buffsize; //размер буффера
};

struct Spisok
{
	Buffer* buf;
	Spisok* next;
};

#endif