#include "medida/medida.h"
#include <unistd.h>

int main() {
    medida::MetricsRegistry registry;
    auto& counter = registry.NewCounter({"foo", "bar", "baz"});
    counter.inc();

    medida::reporting::CollectdReporter collectdReporter(registry);
    collectdReporter.Start(std::chrono::seconds(1));
    //    auto &histogram = registry.histogram({"histogram", "bar", "baz"}, medida::SamplingInterface::kUniform);
    //    auto &timer = registry.timer({"test", "bar", "baz"});
    //    auto &meter = registry.meter({"foo1", "bar", "baz"}, "things");
    auto &value = registry.NewValue({"fooo", "bar", "value"});
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


    collectdReporter.Shutdown();
    return 0;
}
