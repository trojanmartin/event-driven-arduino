#include <Interro.hpp>

/*
 * atm_timer_millis::set( v ) - Sets a millis timer to 'v'
 *
 */

void TimerMillis::set(uint32_t v)
{
  value = v;
}

/*
 * atm_timer_millis::expired( this ) - Checks a millis timer for expiry (== 0)
 * This is a rollover-safe 32 bit unsigned integer comparison
 *
 */

int TimerMillis::expired(Trigger *trigger)
{
  return millis() - trigger->trigger_miliss >= value;
}