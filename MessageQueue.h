#pragma once

#include <atomic>
#include <stdint.h>

// A ring buffer for sending messages to or from the realtime thread.


class MessageQueue {
	public:
		struct Message {
			int	id;
			int64_t	int_value;
			union {
				void*	param;
				double double_value;
				};
			};

		MessageQueue(int capacity = 0);
		~MessageQueue();

		// Sending.
		void send(int message); 	// Send a simple message with no parameters.
		void send(int message, void* param);
		void send(int message, int64_t num);
		void send(int message, double value);
		void send(int message, int64_t num, double value);
		Message* back();
		void push();

		// Receiving.
		Message pop_front();
		Message* front();
		void pop();

		bool is_empty();
		bool is_full();

	protected:
		Message* ring;
		int capacity;
		std::atomic_uint head, tail;
	};



