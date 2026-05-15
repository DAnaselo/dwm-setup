#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FiraCode:size=12" };
static const char dmenufont[]       = "FiraCode:size=12";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#504945";
static const char col_gray3[]       = "#bdae93";
static const char col_gray4[]       = "#fbf1c7";
static const char col_cyan[]        = "#458588";
static const char col_lightcyan[]   = "#83a598";
static const char col_orange[]	    = "#d65d0e";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
[SchemeSel]  = { col_gray4, col_orange, col_orange },
[SchemeStatus]  = { col_gray3, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
[SchemeTagsSel]  = { col_gray4, col_orange,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
[SchemeTagsNorm]  = { col_gray3, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
[SchemeInfoSel]  = { col_gray4, col_gray2,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
[SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty} {text,background,not used but cannot be empty}
};

static const char *const autostart[] = {
  "xset", "r", "rate", "350", "50", NULL,
  "xinput", "set-prop", "7", "libinput Accel Profile Enabled", "0", "1", "0", NULL,
  "/usr/lib/xdg-desktop-portal-gtk", NULL,
  "udiskie", "-at", NULL,
  "nitrogen", "--restore", NULL,
  "slstatus", NULL,
  NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", };
static const Rule rules[] = {
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 180;  /* refresh rate (per second) for client move/resize */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_orange, "-sf", col_gray4, NULL };
static const char *termcmd[]    = { "st", NULL };
static const char *mutecmd[]    = { "wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL };
static const char *volupcmd[]   = { "wpctl", "set-volume", "-l", "1.0", "@DEFAULT_AUDIO_SINK@", "2%+", NULL };
static const char *voldowncmd[] = { "wpctl", "set-volume", "-l", "1.0", "@DEFAULT_AUDIO_SINK@", "2%-", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ Mod1Mask,                     XK_space,  spawn,          {.v = dmenucmd } },
	{ Mod1Mask,                     XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,                       XK_w,      spawn,          SHCMD("xdg-open https://")},
  { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("slock")},
	{ MODKEY,                       XK_e,      spawn,          SHCMD("pcmanfm")},
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
  { 0,                            XF86XK_AudioMute,        spawn, {.v = mutecmd } },
  { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
  { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
