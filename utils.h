#ifndef UTILS_H
#define UTILS_H

// Our random number is actually just the time in ms since startup
// So remember that at the same exact ms you will have the same exact number
// And that it will loop after 50 days (ok this is not really a constraint)
#define GT_RANDOM millis() 
#define GT_RANDOM_RANGE(mini, maxi) (GT_RANDOM % (mini, maxi)) + mini;

#endif
