struct DialogueLine
{
    int action;
    int sound_id;
    int ch_id;
    int emo_id;
    const char *line;
};

enum Characters
{
    CH_BERYL,
    CH_CASTOR,
    CH_NONE
};

enum Emotions
{
    SIT_NORMAL,
    SIT_CONFUSED,
    EMO_SURPRISED,
    EMO_NORMAL,
    EMO_CONFUSED,
    EMO_SAD,
};

enum Actions
{
    SAY,
    EXIT,
    SKIP,
    BERYL_LEFT,
    BERYL_RIGHT,
    CASTOR_APPEAR,
    CASTOR_DISAPPEAR,
    PLAY_WELCOME
};

const DialogueLine gamelines[64][64] = {

    // Test0
    {
        {PLAY_WELCOME, 0, CH_CASTOR, SIT_CONFUSED, "?"},
        {CASTOR_APPEAR, 0, CH_CASTOR, SIT_CONFUSED, "?"},
        {SAY, 0, CH_BERYL, SIT_CONFUSED, "Hey?!   Wh.. What.. Who are you??"},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "Finally. You're ready to remember."},
        {SAY, 0, CH_BERYL, SIT_CONFUSED, "Do I.. know you?"},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "Oh, no.. My name is Castor."},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "You must be Beryl Weiss."},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "I'm delighted to meet you."},
        {SAY, 0, CH_BERYL, SIT_CONFUSED, "..That sounds right..?"},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "There's no easy way to say this, but.."},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "You were in a very bad accident."},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "Right now, you're in a coma."},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "I'm a brand new, experimental treatment."},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "My goal is to help you remember..."},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "And once you do, you'll wake back up."},
        {SAY, 0, CH_BERYL, SIT_CONFUSED, "Oh.. well.."},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "Just look around your old room."},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "I'm sure it'll make sense in time."},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "I'll come back to check on you later."},
        {SAY, 0, CH_CASTOR, SIT_CONFUSED, "Take care!"},
        {CASTOR_DISAPPEAR, 0, CH_BERYL, SIT_CONFUSED, "I guess that's why it felt familiar."},
        {EXIT}
    },

    // Initial conversation
    {{SAY, 0, CH_BERYL, SIT_CONFUSED, "...My head..."},
     {SAY, 0, CH_BERYL, SIT_NORMAL, "..Where am I?"},
     {SAY, 0, CH_BERYL, SIT_CONFUSED, "...I don't even... remember who I am..."},
     {EXIT}},

    // Sit back on bed
    {{SAY, 0, CH_BERYL, SIT_CONFUSED, "Maybe I should just go back to sleep."},
     {SAY, 0, CH_BERYL, SIT_CONFUSED, "It'll all make sense later."},
     {SAY, 0, CH_BERYL, SIT_CONFUSED, "..."},
     {SAY, 0, CH_BERYL, SIT_CONFUSED, "...No... I'm not that tired..."},
     {EXIT}},

    // Castor init
    {{CASTOR_APPEAR},
     {SAY, 0, CH_BERYL, EMO_SURPRISED, "Hey?! Wh-What.. Who are you??"},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Finally. You're ready to remember."},
     {SAY, 0, CH_BERYL, EMO_SURPRISED, "Do I.. know you?"},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Oh, no.. My name is Castor."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "You must be Beryl Weiss."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "..That sounds right..?"},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "There's no easy way to say this, but.."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "You were in a very bad accident."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Right now, you're in a coma."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "I'm a brand new, experimental treatment."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "My goal is to help you remember..."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "And once you do, you'll wake back up."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "Oh.. well.."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Just look around your old room."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "I'm sure it'll make sense in time."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "I'll come back to check on you later."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Take care!"},
     {CASTOR_DISAPPEAR, 0, CH_BERYL, EMO_NORMAL, "Well.. I guess that's why it felt familiar."},
     {EXIT}}};