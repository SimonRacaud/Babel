/*
** EPITECH PROJECT, 2021
** Clock.hpp
** File description:
** add description
*/
#ifndef BOMBERMAN_CLOCK_HPP
#define BOMBERMAN_CLOCK_HPP

#include <chrono>

class Clock {
  public:
    Clock() = default;
    ~Clock() = default;

    /**
     * @brief Set elapsed time since _startingPoint
     */
    void setElapsedTime()
    {
        _elapsedTime = std::chrono::system_clock::now() - _startingPoint;
    }

    /**
     * @brief Get elapsed time in seconds
     *
     * @return Time elapsed since last call to resetElapsedTime as duration
     */
    [[nodiscard]] const std::chrono::duration<double> &getElapsedTime() const
    {
        return _elapsedTime;
    }

    /**
     * @brief Get elapsed time in seconds
     *
     * @return Time elapsed since last call to resetElapsedTime as double
     */
    [[nodiscard]] double getElapsedTimeDouble() const
    {
        return _elapsedTime.count();
    }

    /**
     * @brief Set the elapsed time to 0
     */
    void resetStartingPoint()
    {
        _startingPoint = std::chrono::system_clock::now();
    }

  private:
    std::chrono::time_point<std::chrono::system_clock> _startingPoint{std::chrono::system_clock::now()};

    std::chrono::duration<double> _elapsedTime{0};
};

#endif /* !BOMBERMAN_CLOCK_HPP */