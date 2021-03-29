#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

    void LinkedDequeue::Enqueue(Element e) {
        auto node = new DoublyNode(e, back_, nullptr);
        if (size_ == 0) {
            front_ = node;
            back_ = front_;
        } else {
            back_->next = node;
            back_ = node;
        }
        size_++;
    }

    void LinkedDequeue::EnqueueFront(Element e) {
        auto node = new DoublyNode(e, nullptr, front_);
        if (size_ == 0) {
            front_ = node;
            back_ = front_;
        } else {
            front_ -> previous = node;
            front_ = node;
        }
        size_++;
    }

    void LinkedDequeue::Dequeue() {
        if (size_ == 0) {
            throw std::logic_error("cannot not dequeue from empty queue");
        }
        if (size_ == 1) {
            delete front_;
            front_ = nullptr;
            back_ = nullptr;
        } else {
            auto nodeToDelete = front_;
            front_ = nodeToDelete -> next;
            front_->previous = nullptr;
            delete nodeToDelete;
        }
        size_--;
    }

    void LinkedDequeue::DequeueBack() {
        if (size_ == 0) {
            throw std::logic_error("cannot not dequeue from empty queue");
        }
        if (size_ == 1) {
            delete front_;
            front_ = nullptr;
            back_ = nullptr;
        } else {
            auto nodeToDelete = back_;
            back_ = nodeToDelete->previous;
            back_->next = nullptr;
            delete nodeToDelete;
        }
        size_--;
    }

    void LinkedDequeue::Clear() {
        while (size_ != 0) {
            DequeueBack();
        }
        front_ = nullptr;
    }

// === РЕАЛИЗОВАНО ===

    LinkedDequeue::~LinkedDequeue() {
        Clear();
    }

    std::optional<Element> LinkedDequeue::front() const {
        return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
    }

    std::optional<Element> LinkedDequeue::back() const {
        return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
    }

    bool LinkedDequeue::IsEmpty() const {
        return size_ == 0;
    }

    int LinkedDequeue::size() const {
        return size_;
    }

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

    std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
        os << "size: " << queue.size_ << '\n';
        for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
            if (current_node == queue.front_) os << "[FRONT] ";
            if (current_node == queue.back_) os << "[BACK] ";
            os << enum2str(current_node->data) << '\n';
        }
        return os;
    }

}  // namespace itis
