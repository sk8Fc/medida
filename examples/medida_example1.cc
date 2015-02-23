#include "medida/medida.h"

int main(int argc, char* argv[]) {
    medida::MetricsRegistry registry;
    auto& counter = registry.NewCounter({"foo", "bar", "baz"});
    counter.inc();

    medida::MetricsRegistry registry;
    medida::reporting::CollectdReporter collectdReporter(registry);
    collectdReporter.start(std::chrono::seconds(1));
    //    auto &histogram = registry.histogram({"histogram", "bar", "baz"}, medida::SamplingInterface::kUniform);
    //    auto &timer = registry.timer({"test", "bar", "baz"});
    //    auto &meter = registry.meter({"foo1", "bar", "baz"}, "things");
    auto &value = registry.value({"fooo", "bar", "value"});
    for (int i = 0; i < 10000000; ++i) {

        long ts = rand() % 556;
        //        histogram.update(ts);
        value.update(ts);
        //        usleep(ts);
        //        meter.mark(ts);
        //        auto context = timer.time();
        //        collectdReporter.run();
        usleep(ts);
        //        context.stop();
    }


    collectdReporter.shutdown();
    return 0;
}
