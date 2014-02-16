#include <percentageLife.h>
#include <cassert>
#include <algorithm>
#include <iostream>

namespace EUSDAB
{
    PercentageLife::PercentageLife(const Amount & min, const Amount & max):
        Life(), _percentage(min), _min(min), _max(max)
    {
        assert(_min <= _max);
    }

    bool PercentageLife::isAlive() const
    {
        return true;
    }

    Life::Ratio PercentageLife::receiveDamage(const PercentageLife::Amount & dmg)
    {
        static constexpr Life::Ratio max = 300;
        static constexpr Life::Ratio factor = 4;

        _percentage = std::min(_percentage + dmg, _max);

        std::cout << "Life : " << _percentage << "%" << std::endl;

        return factor * static_cast<Life::Ratio>(_percentage)
            / static_cast<Life::Ratio>(max);
    }

    void PercentageLife::healDamage(const Life::Amount & heal)
    {
        _percentage = std::max(_percentage + heal, _min);
    }

    Life::Amount PercentageLife::amount() const
    {
        return _percentage;
    }

    void PercentageLife::reset()
    {
        _percentage = _min;
    }
}
