
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

  public:
    /**
     * The minimum letter which is valid to be inputted.
     * @see Input::predicateIsValidLetter(std::string &)
     */
    static constexpr char MINIMUM_LETTER = 'a';

  public:
    /**
     * The maximum letter which is valid to be inputted.
     * @see Input::predicateIsValidLetter(std::string &)
     */
    static constexpr char MAXIMUM_LETTER = 'g';

  public:
    /**
     * The letter which must be the presented at first, when validating
     * the testArray.
     * @see Input::validateTestArray(std::string *, int)s
     */
    static constexpr char FIRST_LETTER = 'f';

  public:
    /**
     * The letter which after it the user needs to provide 2 parameters.
     * @see Input::validateTestArray(std::string *, int)
     */
    static constexpr char ALLOWED_TWO_PARAMETERS_LETTER = 'f';
};

#endif // CONSTANTS_H
