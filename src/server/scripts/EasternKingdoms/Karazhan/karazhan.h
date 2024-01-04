#ifndef DEF_KARAZHAN_H
#define DEF_KARAZHAN_H

enum eEnums
{
    TYPE_ATTUMEN                    = 1,
    TYPE_MOROES                     = 2,
    TYPE_MAIDEN                     = 3,
    TYPE_OPTIONAL_BOSS              = 4,
    TYPE_OPERA                      = 5,
    TYPE_CURATOR                    = 6,
    TYPE_ARAN                       = 7,
    TYPE_TERESTIAN                  = 8,
    TYPE_NETHERSPITE                = 9,
    TYPE_CHESS                      = 10,
    TYPE_MALCHEZZAR                 = 11,
    TYPE_NIGHTBANE                  = 12,

    DATA_OPERA_PERFORMANCE          = 13,
    DATA_OPERA_OZ_DEATHCOUNT        = 14,

    DATA_KILREK                     = 15,
    DATA_TERESTIAN                  = 16,
    DATA_MOROES                     = 17,
    DATA_GO_CURTAINS                = 18,
    DATA_GO_STAGEDOORLEFT           = 19,
    DATA_GO_STAGEDOORRIGHT          = 20,
    DATA_GO_LIBRARY_DOOR            = 21,
    DATA_GO_MASSIVE_DOOR            = 22,
    DATA_GO_NETHER_DOOR             = 23,
    DATA_GO_GAME_DOOR               = 24,
    DATA_GO_GAME_EXIT_DOOR          = 25,

    DATA_IMAGE_OF_MEDIVH            = 26,
    DATA_MASTERS_TERRACE_DOOR_1     = 27,
    DATA_MASTERS_TERRACE_DOOR_2     = 28,
    DATA_GO_SIDE_ENTRANCE_DOOR      = 29,
    DATA_NIGHTBANE                  = 30,
    DATA_ECHO_OF_MEDIVH             = 31
};

enum OperaEvents
{
    EVENT_OZ                        = 1,
    EVENT_HOOD                      = 2,
    EVENT_RAJ                       = 3
};

enum MiscCreatures
{
    NPC_HYAKISS_THE_LURKER          = 16179,
    NPC_ROKAD_THE_RAVAGER           = 16181,
    NPC_SHADIKITH_THE_GLIDER        = 16180,

    // Trash
    NPC_COLDMIST_WIDOW              = 16171,
    NPC_COLDMIST_STALKER            = 16170,
    NPC_SHADOWBAT                   = 16173,
    NPC_VAMPIRIC_SHADOWBAT          = 16175,
    NPC_GREATER_SHADOWBAT           = 16174,
    NPC_PHASE_HOUND                 = 16178,
    NPC_DREADBEAST                  = 16177,
    NPC_SHADOWBEAST                 = 16176
};
 
#define ERROR_INST_DATA(a)          sLog->outError(LOG_FILTER_TSCR," Instance Data for Karazhan not set properly. Encounter for Creature Entry %u may not work properly.", a->GetEntry());
#endif