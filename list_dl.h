#ifndef LISTDL_H
#define LISTDL_H
#include <iostream> 
#include <sstream>
#include "node_dl.h"

using namespace std;

template<class T> 
class ListDL{
    NodeDL<T> *head , *tail;
    int length;
    bool ascend;

    void insertAscending( T value) 
    {
        NodeDL<T> * temp = new NodeDL<T>(value);
        if (head == NULL && tail == NULL){ // se head e tail sono nulli allora inserisci in testa 
            this-> insertHead(value);
            return;
        }
        if (head->getValue()>value){ // se il valore in testa è maggiore 
            this->insertHead(value);
            return;
        }
        if(tail->getValue()<=value){
            this->insertTail(value);
            return;
        }

        
        NodeDL<T> * current = head;

        // condizione di arresto = nodo corrente  miniore di value e nodo successivo maggiore o uguale 
        while (current-> getValue() < value){
            current = current->getNext();
        }
        temp->setPrev(current-> getPrev());
        temp-> setNext(current);
        current->getPrev()-> setNext(temp);
        current-> setPrev(temp);
        length++;
    }

     void insertDiscending(T value){
         NodeDL<T> * temp=new NodeDL<T>(value);
        if( head== NULL && tail == NULL){
            this-> insertHead(value);
            return;
        }

        if ( head -> getValue()<= value){
            this-> insertHead(value);
            return;
        }

        if ( tail -> getValue()>value){
            this->insertTail(value);
            return;
        }

      NodeDL<T> * current = tail;

        while ( current->getValue()<= value){
            current = current->getPrev();
        }
        temp->setNext(current->getNext());
        temp->setPrev(current);
        if (current->getNext()) current->getNext()->setPrev(temp);
        current->setNext(temp);

        length++;
    }

    public:
 
    //ListDL() :head(NULL),tail(NULL),length(0),ascend(true){} // creo un costruttore in questo modo ,
    ListDL(): ListDL(true){}
    ListDL(bool ascend): head (NULL) , tail (NULL), length(0),ascend(ascend){} // creo un costruttore che riceva dei parametri in ingresso, bool in questo caso

    //setter e getter

    void setAscendingOrdering (){ ascend= true;} // poichè sto chiamando questo medoto ascending allora passo direttamente io il parametro ascending come true
    void setDescendingOrdering() {ascend = false;}

    NodeDL<T> * getHead() const {return this->head;} //const in questo caso viene usato quando quando vogliamo dichiarare che un metodo non modifichi i campi della classe 
    NodeDL<T> * getTail() const {return this->tail;}
    bool isAscending() const {return this->ascend;}
    int getLength() const {return this-> length;}

    void insertHead(T value){
        NodeDL<T> * temp = new NodeDL<T>(value);
        if ( head == NULL){ // se la testa è vuota è il mio nodo temporaneo che ho creato
            head = temp;
            tail = temp;}
        
        else{
            temp->setNext(head);
            head->setPrev(temp);
            head = temp; 
        }
        length++;
    }

    void insertTail(T value){  
        NodeDL<T> * temp = new NodeDL<T>(value);

        if(head== NULL && tail==NULL){
            head = temp;
            tail = temp; 
        }

        else{
            temp->setPrev(tail) ; 
            tail -> setNext(temp) ; 
            tail= temp;
        }
        length++; 
    }

    void insert(T value){
        if(this->isAscending())
            this->insertAscending(value); 
        else   
            this->insertDiscending(value);
        return;
    }

    void deleteValue(T value){
        NodeDL<T> * cur = head;
        while ( cur != NULL && cur-> getValue() != value ){
            cur= cur-> getNext();
        }
        if (cur ==NULL) // nel caso in cui la lista viene fatta scorrere tutta e non troviamo il valore
        {
            cout << " ERRORE : VALUE= " << value <<" not found !?!?!?"<<endl;
            return ; 
        }
        if (cur != head)
            cur->getPrev()->setNext(cur->getNext());
        if (cur!= tail)
            cur->getNext()->setPrev(cur->getPrev());
        length--;

        if ( cur == head)
            head=head->getNext();    
        if ( cur == tail)
            tail = tail->getPrev();

        delete cur; 
        
    }
    
    friend ostream& operator<<(ostream& out, const ListDL<T> list){
        out << "Lista di lunghezza"<<list.length<<", head="<<list.head<< "; tail="<<list.tail <<endl;
        NodeDL<T> * cur = list.head;
        while(cur != NULL){
            out<< "\t"<< *cur << endl;
            cur= cur->getNext();
        }
        return out;

    }

};



#endif