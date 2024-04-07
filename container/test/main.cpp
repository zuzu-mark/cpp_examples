#include <stdio.h>

#include <boost/thread/thread.hpp>
#include <iostream>

#include "blocking_ring.h"
#include "logger.h"

static constexpr int kPacketBufferSize = 36000;
BlockingRing<int, kPacketBufferSize> decoded_packets_buffer_;

// boost::thread *recieve_packet_thread_ptr_;
std::shared_ptr<std::thread> spthread_;
std::shared_ptr<std::thread> spthread2_;
// boost::thread *parser_thread_ptr_;

void RecieveUdpThread() {
    // std::cout << "RecieveUdpThread" << std::endl;
    LogDebug("bbbb:%s", "RecieveUdpThread");
#if 1
    int decoded_packet;

    // if (decoded_packets_buffer_.empty()) {
    //  std::cout << "empty2" << std::endl;
    //} else {
    // std::cout << "not-empty2: " << decoded_packets_buffer_.front() <<
    // std::endl;
    //}

    decoded_packets_buffer_.try_pop_front(decoded_packet);
    // std::cout << "[end]RecieveUdpThread" << std::endl;
#endif
}

void ParserThread() {
    // std::cout << "ParserThread" << std::endl;
    LogDebug("bbbb:%s", "ParserThread");
#if 1
    int decoded_packet;

    // if (decoded_packets_buffer_.empty()) {
    //   std::cout << "empty3" << std::endl;
    //} else {
    //  std::cout << "not-empty3: " << decoded_packets_buffer_.front() <<
    //  std::endl;
    // }

    decoded_packets_buffer_.try_pop_front(decoded_packet);
    // std::cout << "[end]ParserThread" << std::endl;
#endif
}

// template <typename T_Point>
// void Lidar<T_Point>::
void SetThreadNum(int nThreadNum) {
#if 0
  if (nThreadNum > GetAvailableCPUNum() - 2) {
    nThreadNum = GetAvailableCPUNum() - 2;
  }

  if (handle_thread_count_ == nThreadNum) {
    return;
  }

  running_ = false;

  if (recieve_packet_thread_ptr_ != nullptr) {
    recieve_packet_thread_ptr_->join();
    delete recieve_packet_thread_ptr_;
    recieve_packet_thread_ptr_ = nullptr;
  }

  for (int i = 0; i < handle_thread_count_; i++) {
    if (handle_thread_vec_[i] != nullptr) {
      handle_thread_vec_[i]->join();
      delete handle_thread_vec_[i];
      handle_thread_vec_[i] = nullptr;
    }

    handle_thread_packet_buffer_[i].clear();
  }

  running_ = true;
#endif

#if 0
  if (nThreadNum > 1) {
    handle_thread_vec_.resize(nThreadNum);
    handle_thread_packet_buffer_.resize(nThreadNum);

    for (int i = 0; i < nThreadNum; i++) {
      boost::arg<1> _1;
      handle_thread_vec_[i] = new boost::thread(
          boost::bind(&Lidar::HandleThread, this, _1), i);
    }
  }

  handle_thread_count_ = nThreadNum;
#endif

    // recieve_packet_thread_ptr_ = new boost::thread(&RecieveUdpThread);
    spthread_.reset(new std::thread(&RecieveUdpThread));
    spthread2_.reset(new std::thread(&ParserThread));
    // parser_thread_ptr_ = new boost::thread(&ParserThread);
}

#include <signal.h>
std::mutex g_mtx;
std::condition_variable g_cv;

static void sigHandler(int sig) { g_cv.notify_all(); }

static int packet = 1;
#include <stdarg.h>

void logCallback(LOGLEVEL loglevel, const char *pszFile, int lineNo,
                 const char *pszFuncSig, const char *pszFmt, ...) {
    char msg[256] = {0};
    std::cout << "logcallback" << std::endl;
    va_list vArgList;
    va_start(vArgList, pszFmt);
    vsnprintf(msg, 256, pszFmt, vArgList);
    va_end(vArgList);
    std::cout << "logcallback2" << msg << std::endl;
}
int init(void) {
    /*******************************Init
     * log*********************************************/
    Logger::GetInstance().SetFileName("test.log");
    Logger::GetInstance().setLogTargetRule(
        (LOG_TARGET_FILE));  // | LOG_TARGET_CONSOLE));
    Logger::GetInstance().setLogLevelRule(LOG_DEBUG);
    // Logger::GetInstance().bindLogCallback(logCallback);
    Logger::GetInstance().Start();
    /**********************************************************************************/
    return 0;
}
int main(int argc, const char *argv[]) {
    // printf("hello world\n");
    init();

    signal(SIGINT, sigHandler);

    decoded_packets_buffer_.push_back(std::move(packet));
    if (decoded_packets_buffer_.empty()) {
        // std::cout << "empty1" << std::endl;
    } else {
        // std::cout << "not-empty1: " << decoded_packets_buffer_.front() <<
        // std::endl;
    }

    SetThreadNum(0);
    // LogDebug("aaaa:%s", "end world3");
    // LogDebug("bbbb:%s", "end world4");

    std::unique_lock<std::mutex> lck(g_mtx);
    g_cv.wait(lck);
    //  while (1)
    //    ;
    //
#if 0
  if (recieve_packet_thread_ptr_ != nullptr) {
    recieve_packet_thread_ptr_->join();
    delete recieve_packet_thread_ptr_;
    recieve_packet_thread_ptr_ = nullptr;
  }
  if (parser_thread_ptr_ != nullptr) {
    parser_thread_ptr_->join();
    delete parser_thread_ptr_;
    parser_thread_ptr_ = nullptr;
  }
#endif
    if (spthread_ != nullptr) {
        spthread_->join();
    }
    if (spthread2_ != nullptr) {
        spthread2_->join();
    }

    // LogDebug("aaaa:%s", "end world2");
    // printf("end world\n");
    Logger::GetInstance().Stop();

    // Logger::GetInstance().~Logger();
    return 0;
}
