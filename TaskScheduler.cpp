using std::chrono::time_literals;
Scheduler::instance().add([]() { std::cout << "Hello" << std::endl; }, 100ms);
Scheduler::instance().add([this]() { checkConfig(); }, 1s);
std::mutex(m);
std::vector<std::thread> pool;

class Scheduler {
 public:
  ~Scheduler() {
    should_stop = true;
    poller.join();
  }
  void add(std::function<void()>&& func,
           const std::chrono::system_time::time_period& period);

 private:
  std::map<std::chrono::system_time::time_point, std::function<void()>> tasks;
};

Scheduler::add(std::function<void()>&& func,
               const std::chrono::system_time::time_period& period) {
  std::unique_lock<mutex> lock(m) tasks.insert(func);
  cond.notify(lock);
}

Scheduler::run() {
poller = std::thread([]() {
    while (!should_stop) {
      If(std::unique_lock<mutex> lock(m);
         tasks.begin().first >= std::chrono::system_time::now()) {
        auto task = *tasks.begin();
        tasks.erase(tasks.begin());
        pool.submit([task]() {
          task.func();
          Scheduler::instance().add(
              task.func, std::chrono::system_time::now() + task.period);
        });
      }
      else {
        auto sleep = task.period - std::chrono::system_time::now();
        cond.wait_for(
            lock, [] { !tasks.empty() }, sleep);
      }
    }
}
