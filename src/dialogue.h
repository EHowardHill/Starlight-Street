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
    CH_MEMORY,
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
    EMO_HAPPY2,
    LAY_STILL,
    LAY_SIT1,
    LAY_SIT2
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
    MUSIC_STOP,
    SFX_SEBENEREBEN,
    GAME_BRACELET
};

const DialogueLine gamelines[64][64] = {

    // Initial conversation
    {{SAY, 0, CH_BERYL, SIT_CONFUSED, "...My head..."},
     {SAY, 0, CH_BERYL, SIT_NORMAL, "..Where am I?"},
     {SAY, 0, CH_BERYL, SIT_CONFUSED, "...I don't even... remember who I am..."},
     {SAY, 0, CH_BERYL, SIT_NORMAL, "I guess it wouldn't hurt to look around."},
     {EXIT}},

    // Sit back on bed
    {{SAY, 0, CH_BERYL, SIT_CONFUSED, "Maybe I should just go back to sleep."},
     {SAY, 0, CH_BERYL, SIT_CONFUSED, "It'll all make sense later."},
     {SAY, 0, CH_BERYL, SIT_CONFUSED, "..."},
     {SAY, 0, CH_BERYL, SIT_CONFUSED, "...No... I'm not that tired..."},
     {EXIT}},

    // Castor init
    {{PLAY_WELCOME, 0, CH_CASTOR, EMO_SURPRISED, "?"},
     {CASTOR_APPEAR, 0, CH_CASTOR, EMO_SURPRISED, "?"},
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
     {CASTOR_DISAPPEAR, 0, CH_BERYL, EMO_NORMAL, "Okay..."},
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

    // door
    {{SAY, 0, CH_BERYL, EMO_NORMAL, "Didn't there.."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "..used to be a door here?"},
     {EXIT}},

    // GRASS!
    {{SAY, 0, CH_BERYL, LAY_STILL, "That's right.       I remember."},
     {SAY, 0, CH_BERYL, LAY_STILL, "It was Christmas. My family had just moved in."},
     {SAY, 0, CH_BERYL, LAY_STILL, "I invited my friend Holly to spend the night."},
     {SAY, 0, CH_BERYL, LAY_STILL, "We made friendship bracelets."},
     {SAY, 0, CH_BERYL, LAY_STILL, "We probably stayed up until Three O'clock."},
     {SAY, 0, CH_BERYL, LAY_STILL, "It was so scandalous, we thought."},
     {SAY, 0, CH_BERYL, LAY_STILL, "I miss Holly."},
     {SAY, 0, CH_BERYL, LAY_STILL, "We moved away from that house."},
     {SAY, 0, CH_BERYL, LAY_STILL, "I wonder if I'll ever be able..."},
     {SAY, 0, CH_BERYL, LAY_STILL, "...you know... to see it again."},
     {SAY, 0, CH_BERYL, LAY_STILL, "..."},
     {SAY, 0, CH_BERYL, LAY_SIT2, "But that's life."},
     {SAY, 0, CH_BERYL, LAY_SIT1, "Why would it change now?"},
     {EXIT}},

    // end of demo
    {
        {SAY, 0, CH_BERYL, EMO_CONFUSED, "..Starlight?"},
        {SAY, 0, CH_BERYL, EMO_SURPRISED, "?"},
        {CASTOR_APPEAR, 0, CH_CASTOR, EMO_SURPRISED, "?"},
        {MUSIC_STOP, 0, CH_BERYL, EMO_SURPRISED, "?"},
        {SAY, 0, CH_CASTOR, EMO_SURPRISED, "Starlight Street!"},
        {SAY, 0, CH_CASTOR, EMO_SURPRISED, "That's the street you used to live at."},
        {SAY, 0, CH_BERYL, EMO_SAD, "...Please don't scare me, Castor"},
        {SAY, 0, CH_BERYL, EMO_SAD, "I almost cried."},
        {SAY, 0, CH_BERYL, EMO_CONFUSED, "That... thing..."},
        {SAY, 0, CH_CASTOR, EMO_NORMAL, "Don't think about it, Beryl."},
        {SAY, 0, CH_CASTOR, EMO_NORMAL, "Negative memories attract it."},
        {SAY, 0, CH_CASTOR, EMO_NORMAL, "Focus on the positive, okay?"},
        {SAY, 0, CH_BERYL, EMO_NORMAL, "I'll... do my best."},
        {SAY, 0, CH_CASTOR, EMO_NORMAL, "Just follow me for a moment."},
        {SAY, 0, CH_CASTOR, EMO_NORMAL, "Let's go somewhere new, yes?"},
        {SAY, 0, CH_CASTOR, EMO_NORMAL, "It will help you remember."},
        {EXIT}},

    // conbini first
    {{SAY, 0, CH_BERYL, EMO_NORMAL, "I've been here before. I know it."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Never at night, though."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "Never alone either."},
     {CASTOR_APPEAR, 0, CH_BERYL, EMO_SURPRISED, "?"},
     {SAY, 0, CH_CASTOR, EMO_SURPRISED, "You're not alone now."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "I swear... You scare me every time I see you."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "This location is a little.. mixed."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "There were good and bad feelings here."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Useful.. but dangerous."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Just talk to me if you need anything."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "I'll be by the back door!"},
     {CASTOR_DISAPPEAR, 0, CH_BERYL, EMO_CONFUSED, "?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Memories... Memories..."},
     {SAY, 0, CH_BERYL, EMO_SAD, "None of this feels right..."},
     {EXIT}},

    {{SAY, 0, CH_BERYL, EMO_HAPPY2, "...it was after school! That's right."},
     {SAY, 0, CH_BERYL, EMO_HAPPY1, "Almost every single day when we were friends."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "I don't.. remember having a job."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "Where did the money come from?"},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "Was I rich?"},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "I don't remember nice things..."},
     {SAY, 0, CH_BERYL, EMO_SAD, "Actually, I think..."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "No. No bad memories."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "I'm not letting that.. thing.. return."},
     {EXIT}},

    {{SAY, 0, CH_BERYL, EMO_HAPPY2, "Soda. I stopped drinking that."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "It was.. for some reason.."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I do remember getting snacks here."},
     {SAY, 0, CH_BERYL, EMO_HAPPY1, "I think Holly was there too."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "What did she look like again?"},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "This is gonna kill me..."},
     {EXIT}},

    {{SAY, 0, CH_BERYL, EMO_HAPPY2, "What was my favorite ice cream flavor?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I think it changed at some point."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I'd like to have it again someday."},
     {SAY, 0, CH_BERYL, EMO_HAPPY1, "After I wake up."},
     {EXIT}},

    {{SAY, 0, CH_BERYL, EMO_HAPPY2, "Hm.. I can't smell anything, but.."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I didn't like this part of the store."},
     {CASTOR_APPEAR, 0, CH_BERYL, EMO_SURPRISED, "?"},
     {SAY, 0, CH_CASTOR, EMO_SURPRISED, "Do you need anything from me?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Thanks, Castor, but, uh.."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "I think I'm fine."},
     {SAY, 0, CH_CASTOR, EMO_SURPRISED, "You look confused."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Well.. yeah, of course I do."},
     {SAY, 0, CH_CASTOR, EMO_SURPRISED, "What are you wondering?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I don't know enough to ask."},
     {SAY, 0, CH_CASTOR, EMO_SURPRISED, "Okay, just find the good memories."},
     {SAY, 0, CH_CASTOR, EMO_SURPRISED, "If you think you'll be sad..."},
     {SAY, 0, CH_CASTOR, EMO_SURPRISED, "Just think about something else, okay?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I'll try my best."},
     {CASTOR_DISAPPEAR, 0, CH_BERYL, EMO_CONFUSED, "?"},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "What a weird.. shape."},
     {EXIT}},

    {{SAY, 0, CH_BERYL, EMO_HAPPY1, "I remember I wanted a car."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "My.. oh.. who was he.."},
     {SAY, 0, CH_BERYL, EMO_SURPRISED, "My.. older brother? I had a brother?"},
     {SAY, 0, CH_BERYL, EMO_HAPPY2, "I did.. He would drive me."},
     {SAY, 0, CH_BERYL, EMO_SAD, "I still wanted a car."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "This world is so small, though."},
     {SAY, 0, CH_BERYL, EMO_SAD, "I bet there's nowhere to drive to."},
     {EXIT}},

    {{SFX_SEBENEREBEN, 0, CH_BERYL, EMO_HAPPY2, "?"},
     {SAY, 0, CH_BERYL, EMO_HAPPY2, "Aw! I remember that sound!"},
     {SAY, 0, CH_BERYL, EMO_HAPPY1, "..."},
     {SAY, 0, CH_BERYL, EMO_SAD, "I wonder if this place still exists."},
     {SAY, 0, CH_BERYL, EMO_SAD, "Even if it does..."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "No.. focus on the moment."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "I'm here right now."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "And that's enough."},
     {EXIT}},

    // Numbering doesn't count

    {{CASTOR_APPEAR, 0, CH_BERYL, EMO_SURPRISED, "?"},
     {SAY, 0, CH_CASTOR, EMO_SURPRISED, "Hello, Beryl.. Are you alright?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Yeah.. How long is this supposed to last?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "As long as you want it to."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "I don't like these memories..."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "How hard would it be to just.. y'know.."},
     {SAY, 0, CH_BERYL, EMO_SAD, "Go back to Corner's and stay there."},
     {SAY, 0, CH_CASTOR, EMO_SAD, "If you don't want to continue.."},
     {SAY, 0, CH_CASTOR, EMO_SAD, "There is nothing keeping you from staying there."},
     {SAY, 0, CH_CASTOR, EMO_SAD, "You can even stay forever if you want."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "I don't.. want to stay here forever."},
     {SAY, 0, CH_CASTOR, EMO_CONFUSED, "If you see things that hurt.."},
     {SAY, 0, CH_CASTOR, EMO_CONFUSED, "And you want to change your mind.."},
     {SAY, 0, CH_CASTOR, EMO_CONFUSED, "The option is always available."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "So.. what is that monster, anyway?"},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Oh, don't worry about her."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "'Her'? What do you mean by 'her'?"},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "It's not important, Beryl."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Castor.. Are you hiding something?"},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "You look stressed. Be careful."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "If you get upset, it will return."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Maybe I want it to."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "You don't. I can assure you."},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "Well... I don't know."},
     {SAY, 0, CH_BERYL, EMO_SAD, "I don't know anything anymore."},
     {SAY, 0, CH_CASTOR, EMO_SAD, "Let's move on, shall we?"},
     {EXIT}},

    {{SAY, 0, CH_BERYL, LAY_STILL, "It's coming back to me..."},
     {SAY, 0, CH_BERYL, LAY_STILL, "I got bored of theatre my senior year."},
     {SAY, 0, CH_BERYL, LAY_STILL, "I followed my friends to art class."},
     {SAY, 0, CH_BERYL, LAY_STILL, "I met a boy. Capricorn."},
     {SAY, 0, CH_BERYL, LAY_STILL, "We dated maybe six months."},
     {SAY, 0, CH_BERYL, LAY_STILL, "One day he stopped texting."},
     {SAY, 0, CH_BERYL, LAY_STILL, "Graduation wasn't long after."},
     {SAY, 0, CH_BERYL, LAY_STILL, "Everyone went off to college."},
     {SAY, 0, CH_BERYL, LAY_STILL, "Friendship is based on circumstance."},
     {SAY, 0, CH_BERYL, LAY_STILL, "I became very alone, very quickly."},
     {SAY, 0, CH_BERYL, LAY_STILL, "I was looking forward to college..."},
     {SAY, 0, CH_BERYL, LAY_SIT2, "I thought I was looking forward..."},
     {SAY, 0, CH_BERYL, LAY_SIT1, "But I spent most of my time, well..."},
     {SAY, 0, CH_BERYL, LAY_SIT1, "Looking backward."},
     {EXIT}},

    {{CASTOR_APPEAR, 0, CH_BERYL, EMO_SURPRISED, "?"},
     {SAY, 0, CH_CASTOR, EMO_SURPRISED, "How are you feeling?"},
     {SAY, 0, CH_BERYL, EMO_SAD, "Awful.. Just awful.."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "You looked happy around Corner's."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Remember that? Would you like to stay?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "...You keep saying 'stay'."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "What are you after?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I thought your job was to wake me up."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "My job is to help you be happy."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "Would it make you happier to stay?"},
     {SAY, 0, CH_BERYL, EMO_CONFUSED, "It might, but..."},
     {SAY, 0, CH_CASTOR, EMO_CONFUSED, "Very good!"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Castor, may I ask you something?"},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "What is it, Beryl?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Who... are you? Really."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "I'm Castor, I'm-"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Quit lying to me."},
     {SAY, 0, CH_CASTOR, EMO_NORMAL, "I'm not lying to you, Beryl."},
     {EXIT}},

    {{SAY, 0, CH_BERYL, EMO_SAD, "Awful.. Just awful.."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "You looked happy around Corner's."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Remember that? Would you like to stay?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "...You keep saying 'stay'."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "What are you after?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I thought your job was to wake me up."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "My job is to help you be happy."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Would it make you happier to stay?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "It might, but..."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Very good!"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Castor, may I ask you something?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "What is it, Beryl?"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Who... are you? Really."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I'm Castor, I'm-"},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "Quit lying to me."},
     {SAY, 0, CH_BERYL, EMO_NORMAL, "I'm not lying to you, Beryl."},
     {EXIT}},

    {{SAY, 0, CH_MEMORY, EMO_SAD, "I've always been with you, Beryl."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "Nostalgia, my twin, it makes him jealous."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "He lies so you will stay with him."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "Nothing he offers is his to give."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "That happy distraction..."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "It's why you got in that car wreck."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "He put you in this coma."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "Beryl.. you've done crummy things."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "But this experience is a gift."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "All the compromises that led to now..."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "You don't remember them."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "All that's left is the true Beryl."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "Don't fight for what you think the past was."},
     {SAY, 0, CH_MEMORY, EMO_NORMAL, "Fight for what made the past good."},
     {EXIT}},

};

/*

Choices:
> No. I want to stay forever.
> It's time to take up.

*/