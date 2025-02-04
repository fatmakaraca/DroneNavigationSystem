#include "Queue.h"
#include <iostream>

// Constructor to initialize an empty queue
Queue::Queue() {
    // TODO: Your code here
    number_of_data = 0;
    front = -1;
    rear = -1;
}

// Adds a province to the end of the queue
void Queue::enqueue(int province) {
    // TODO: Your code here
    // Implement circular structure 
    // Add the province  
    if(number_of_data == MAX_QUEUE_SIZE){
        std::cout<<"queue is full"<<std::endl;
        return;
    }

    if(number_of_data == 0){
        front = 0;
        rear = 0;
    }else{
        rear = (rear + 1) % MAX_QUEUE_SIZE;
    }

    number_of_data++;
    data[rear] = province;
}

// Removes and returns the front province from the queue
int Queue::dequeue() {
    // TODO: Your code here
    if(isEmpty()==false){
        int value = data[front];
        front = (front + 1) % MAX_QUEUE_SIZE;
        number_of_data--;
        if (number_of_data == 0) {
            front = rear = -1;
        }
        return value;
    }else{
        std::cout<<"queue is empty"<<std::endl;
        return -1;
    }
    return 0;
}

// Returns the front province without removing it
int Queue::peek() const {
    // TODO: Your code here
    if(isEmpty()==false){
        int value = data[front];
        return value;
    }else{
        std::cout<<"queue is empty"<<std::endl;
        return -1;
    }
    return 0;
}

// Checks if the queue is empty
bool Queue::isEmpty() const {
    // TODO: Your code here
    return front == -1;
}

// Add a priority neighboring province in a way that will be dequeued and explored before other non-priority neighbors
void Queue::enqueuePriority(int province) {
    // TODO: Your code here
    if (number_of_data == MAX_QUEUE_SIZE) { // Kuyruk dolu
        std::cout << "Queue is full!" << std::endl;
        return;
    }

    if(isEmpty()){
        enqueue(province);
        return;
    }

    front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    data[front] = province;
    number_of_data++;
}

