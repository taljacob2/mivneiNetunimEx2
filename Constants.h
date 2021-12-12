
#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants {

  public:
    /// Defines the char for 'new-line' used in the program.
    static constexpr char NEW_LINE = '\n';

  public:
    /// The return value of `main` function, to be returned in case of a failure.
    static constexpr int MAIN_ERROR = 1;

  public:
    /// The text to be presented when there is a wrong input.
    static constexpr char *WRONG_INPUT = (char *) "wrong input";
};

#endif // CONSTANTS_H
