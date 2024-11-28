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
    EMO_NORMAL,
    EMO_SURPRISED,
    EMO_CONFUSED,
    EMO_SAD,
    EMO_HAPPY1,
    EMO_HAPPY2
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
    PLAY_WELCOME,
    GAME_BRACELET
};

const DialogueLine gamelines[64][64] = {

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
    {{PLAY_WELCOME, 0, CH_CASTOR, SIT_CONFUSED, "?"},
     {CASTOR_APPEAR, 0, CH_CASTOR, SIT_CONFUSED, "?"},
     {SAY, 0, CH_BERYL, EMO_SURPRISED, "Hey?!  What... or.. Who are you??"},
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
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "..."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Just look around your old room."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "I'm sure it'll make sense in time."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "I'll come back to check on you later."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Take care!"},
     {CASTOR_DISAPPEAR, 0, CH_BERYL, EMO_NORMAL, "Well.. I guess that's why it felt familiar."},
     {EXIT}},
     
    // Sit back on bed
    {{SAY, 0, CH_BERYL, EMO_SURPRISED, "Huh.. That's kind of funny."},
     {SAY, 0, CH_BERYL, EMO_SURPRISED, "It kinda looks like.. No.."},
     {SAY, 0, CH_BERYL, EMO_SURPRISED, "That can't be right.."},
     {EXIT}},

    // desk
    {{SAY, 0, CH_BERYL, EMO_HAPPY2, "Hey.. I think I used to.. draw."},
     {SAY, 0, CH_BERYL, EMO_HAPPY2, "I wonder if I still have it in me."},
     {SAY, 0, CH_BERYL, EMO_HAPPY2, "..Those prismacolors were expensive."},
     {SAY, 0, CH_BERYL, EMO_HAPPY1, "I never wanted to use em."},
     {SAY, 0, CH_BERYL, EMO_HAPPY1, "They were so pretty though."},
     {EXIT}},

    // shelf
    {{SAY, 0, CH_BERYL, EMO_SURPRISED, "That's.. a friendship bracelet!"},
     {SAY, 0, CH_BERYL, EMO_HAPPY1, "I made when it when I was a kid with.."},
     {SAY, 0, CH_BERYL, EMO_SAD, "Oh my god, what's her name..."},
     {GAME_BRACELET, 0, CH_BERYL, EMO_SAD, "?"},
     {EXIT}},

     // closet
    {{SAY, 0, CH_BERYL, EMO_NORMAL, "That's.. I don't remember.."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I don't remember what's in there."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I hear something, though..."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "I think... I should leave it closed."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "It gives me a bad feeling."},
     {EXIT}},

     // closet
    {{SAY, 0, CH_BERYL, EMO_HAPPY2, "Hey, that's a prize ribbon!"},
     {SAY, 0, CH_BERYL, EMO_HAPPY1, "I must have won an award."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I don't.. remember what I painted."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "That's.. a little odd."},
     {EXIT}},

     // closet
    {{SAY, 0, CH_BERYL, EMO_NORMAL, "Didn't there.."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "..used to be a door here?"},
     {EXIT}},
     
     };