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

};

/*


I was a freshman in high school.
Mom and dad never liked each other,
...or at least that's what they said.
I always thought it wasn't true.
I guess they finally had enough one day.
One day, after school, Holly took me to Corners.
She got me ice cream. It was Dutch chocolate.
It became a tradition before too long.
The station has since been remodeled.
I haven't been in years. No reason.
It's funny how you forget places like that.

I tried out for theatre sophomore year.
Holly tried but didn't make it.
I really wanted the theatre kids to like me.
One day, after school, I went over to one of the other girls' houses.
She was the lead in our one-act play.
She dared me to give Holly a mean phone call.
It was very, very mean.
I don't know why I did it.
That was the last time I spoke to her.

Beryl: How long does this go on?
Castor: - As long as you want it to.
I saw a glimpse... It was me and Holly.
Can I go back to that?
- Yes! You may.
I don't even know if I want to wake up...
If I could just stay there.
- Well, if you insist, you can stay forever.
Forever?
- Forever and ever.
...That's a long time.
- It doesn't feel like it.
I guess... I have to know...
What is... that monster?
Is that a memory?
- The monster? Don't worry about her.
Her? What do you mean by 'her'?
- I... I mean...
Castor, are you hiding something? 
- Be careful, Beryl, it'll come back.
Maybe I want it to.
- You don't, I can assure you.
...You're probably right.
- Very good. Let's move on, shall we?

Senior year, I got bored of theatre.
A lot of my friends started taking art class.
That's where I met Capricorn.
I think we dated for maybe six months.
I liked the attention.
One day he just stopped texting.
That's the thing about high school...
Everyone goes off to college.
Circumstantial friends stop talking to you.
I ended up very, very alone.
I was looking forward to college, though...
At least, I think I was looking forward.
I spent a lot of time looking backward.

- So, how do you feel?
Terrible.
- You looked pretty happy around Corners.
- With the ice cream? Dutch chocolate?
I was.
- Is that where you'd like to stay?
You keep saying 'stay'.
I thought your job was to wake me up.
- Only if you want to be awoken.
...Something isn't adding up here.
Who... are you? Really.
- I'm Castor, I'm-
Quit lying to me.
- I'm not lying to you.

MONSTER, who is actually MEMORY:
I have always been you, Beryl.
My twin, Nostalgia, he is so jealous.
He will lie as much as it takes.
And as if 2018 were even his to give.
That happy thought, that distraction...
It's why you got in that car wreck.
It's why you're in a coma.
He wants to eat your soul.
Beryl... you've done bad things.
But this experience could be a gift.
All the little mistakes that led to now...
The compromises... they're off to the side.
You only remember the true Beryl, deep down.
Don't fight for 2018.
Fight for what made 2018 good.

Choices:
> No. I want to stay forever.
> It's time to take up.

*/