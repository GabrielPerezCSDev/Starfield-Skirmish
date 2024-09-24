#ifndef STAR_QUEUE_H
#define STAR_QUEUE_H

#include <iostream>
#include <stdexcept>
#include <functional>

struct Star {
    char symbol;  // Symbol representing the star
};

class StarQueue {
private:
    Star*** queue;  // A pointer to a two-dimensional array of Star pointers
    int front, rear, capacity, stripLength;

public:
    StarQueue(int width, int height) : front(0), rear(0), capacity(height), stripLength(width) {
        queue = new Star**[capacity];
        for (int i = 0; i < capacity; ++i) {
            queue[i] = new Star*[stripLength];
            for (int j = 0; j < stripLength; ++j) {
                queue[i][j] = nullptr;  // Initialize with empty entries
            }
        }
    }

    ~StarQueue() {
        for (int i = 0; i < capacity; ++i) {
            for (int j = 0; j < stripLength; ++j) {
                delete queue[i][j];  // Delete each Star object
            }
            delete[] queue[i];  // Delete each sub-array
        }
        delete[] queue;  // Delete the main array
    }

    // dequeue - Remove from the end
    void dequeue() {
        if (front == rear) {  // Check if the queue is empty
            std::cerr << "Queue is empty\n";
            return;
        }

        // Adjust rear to point to the previous array
        rear = (rear - 1 + capacity) % capacity;

        // Delete the stars in the rear strip
        for (int j = 0; j < stripLength; ++j) {
            delete queue[rear][j];
            queue[rear][j] = nullptr;
        }
    }

    // enqueue - Add to the first index
    void enqueue() {
        // Check if the queue is full
        if ((front - 1 + capacity) % capacity == rear) {
            std::cerr << "Queue is full\n";
            return;
        }

        // Adjust front to point to the new first index
        front = (front - 1 + capacity) % capacity;

        // Generate a new strip of stars at the new front
        queue[front] = new Star*[stripLength];
        for (int j = 0; j < stripLength; ++j) {
            if (rand() % 5 == 0) {  // Randomly decide whether to place a star
                queue[front][j] = new Star{'*'};  // Create a new star
            } else {
                queue[front][j] = nullptr;  // Leave the space empty
            }
        }
    }

    void init_queue(){
        //for the length of the queue enqueue a random distribution of stars 
        while ((rear + 1) % capacity != front) {  // Fill the queue until it's full
        enqueue();
        }
    }

    // Method to get the array at a specific index in the queue
    Star** getArray(int index) const {
        if (index < 0 || index >= capacity) {
            throw std::out_of_range("Index out of range");
        }
        return queue[(front + index) % capacity];
    }


    int getCapacity() const {
        return capacity;
    }

    int getStripLength() const {
        return stripLength;
    }

    // Method to print the entire queue
    void printQueue() const {
        std::cout << "StarQueue Contents:" << std::endl;
        int index = front;
        do {
            Star** starArray = queue[index];
            for (int j = 0; j < stripLength; ++j) {
                if (starArray[j] != nullptr) {
                    std::cout << starArray[j]->symbol << " ";
                } else {
                    std::cout << " ";  // Print a placeholder for empty cells
                }
            }
            std::cout << std::endl;
            index = (index + 1) % capacity;
            if (index == rear) break;  // Stop if we've reached the rear
        } while (true);
    }
};

#endif // STAR_QUEUE_H