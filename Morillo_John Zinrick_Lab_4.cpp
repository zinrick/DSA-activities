#include <iostream>
using namespace std;

const int MAX_QUEUE = 10;

struct Song {
    string name;
    int priority;
};

class CircularPriorityQueue {
private:
    Song queue[MAX_QUEUE];
    int front = -1;
    int rear = -1;

    int next(int index) {
        return (index + 1) % MAX_QUEUE;
    }

    int prev(int index) {
        return (index - 1 + MAX_QUEUE) % MAX_QUEUE;
    }

public:
    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return next(rear) == front;
    }

    string enqueue(string name, int priority) {
        if (isFull()) {
            return "The queue is full. Try again later.";
        }

        Song newSong = {name, priority};

        
        if (isEmpty()) {
            front = rear = 0;
            queue[rear] = newSong;
            return "A new song has been added to the queue.";
        }

        
        int i = rear;
        while (true) {
            int j = next(i);
            if (queue[i].priority <= newSong.priority || i == prev(front)) {
                queue[j] = newSong;
                rear = next(rear);
                break;
            }
            queue[j] = queue[i];
            i = prev(i);
        }

        return "A new song has been added to the queue.";
    }

    string dequeue() {
        if (isEmpty()) {
            return "There is no song in the queue. Try adding first.";
        }

        string songName = queue[front].name;

        if (front == rear) {
            front = rear = -1;
        } else {
            front = next(front);
        }

        return "Now playing: " + songName;
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "The queue is empty." << endl;
            return;
        }

        cout << "Songs in the queue:" << endl;
        int i = front;
        while (true) {
            cout << queue[i].name << " (Priority " << queue[i].priority << ")" << endl;
            if (i == rear) break;
            i = next(i);
        }
    }
};

int main() {
    CircularPriorityQueue cpq;

    cout << cpq.enqueue("All or Nothing", 3) << endl;
    cout << cpq.enqueue("Synesthesia", 2) << endl;
    cout << cpq.enqueue("Passenger Seat", 1) << endl;

    cpq.displayQueue();

    cout << cpq.dequeue() << endl;
    cout << cpq.dequeue() << endl;

    cpq.displayQueue();

    return 0;
}