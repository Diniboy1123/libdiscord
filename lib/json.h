/** @file */

#ifndef LIBDISCORD_JSON_H
#define LIBDISCORD_JSON_H

#include <libdiscord.h>
#include <jansson.h>
#include "REST.h"

/*
 * READ:
 * string -> struct
 *
 * SAVE:
 * struct -> string
 *
 * LOAD:
 * string -> json_t
 * string -> (native type)
 *
 * PACK:
 * json_t -> struct
 * (native type) -> struct
 *
 * UNPACK:
 * struct -> json_t
 *
 * DUMP:
 * json_t -> string
 */

/*
 * snowflakes are 64 bit unsigned integers encoded in decimal in a string for maximum compatability with languages that
 * can't handle 64 bit integers
 *
 * something that libdiscord should check to see is that some architectures don't support numbers past a certain size
 * i.e. 32 bit only
 * how we handle that will be interesting
 */
//typedef uint64_t LD_SNOWFLAKE;

/*
 * timestamp types are strings formatted in the ISO8601 format
 */
typedef char * TIMESTAMP;



enum ld_presence_activity_type;
enum ld_json_status_type;
enum ld_activity_flags;




struct ld_json_snowflake;
struct ld_json_status_update;
struct ld_json_identify_connection_properties;
struct ld_json_identify;
struct ld_json_party;
struct ld_json_assets;
struct ld_json_activity;
struct ld_json_secrets;
struct ld_json_gateway_update_status;
struct ld_json_user;
struct ld_json_role;
struct ld_json_attachemnt;
struct ld_json_embed_footer;
struct ld_json_embed_image;
struct ld_json_embed_thumbnail;
struct ld_json_embed_video;
struct ld_json_embed_provider;
struct ld_json_embed_author;
struct ld_json_embed_field;
struct ld_json_embed;
struct ld_json_emoji;
struct ld_json_reaction;
struct ld_json_message_activity;
struct ld_json_message_application;
struct ld_json_message;
struct ld_json_overwrite;
struct ld_json_attachment;
struct ld_json_channel;
struct ld_json_voice_state;
struct ld_json_guild_member;
struct ld_json_guild;
struct ld_json_account;
struct ld_json_ban;
struct ld_json_integration;

struct ld_json_getgateway;
struct ld_json_getgateway_bot;
struct ld_json_getgateway_bot_sessionstartlimit;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
#pragma mark Enumeration declarations
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief activity type
 *
 * <a href="https://discordapp.com/developers/docs/topics/gateway#activity-object-activity-types" Discord API Documentation</a>
 */
enum ld_presence_activity_type {
    LD_PRESENCE_ACTIVITY_PLAYING = 0,
    LD_PRESENCE_ACTIVITY_STREAMING = 1,
    LD_PRESENCE_ACTIVITY_LISTENING = 2
//    LD_PRESENCE_ACTIVITY_WATCHING = 3
};


/**
 * @brief Status enum type
 *
 * enum integer values are used internally, strings are sent in payloads
 *
 * <a href="https://discordapp.com/developers/docs/topics/gateway#update-status-status-types" Discord API Documentation</a>
 */
enum ld_json_status_type {
    LD_PRESENCE_IDLE = 0, ///< "idle"
    LD_PRESENCE_DND = 1, ///< "dnd"
    LD_PRESENCE_ONLINE = 2, ///< "online"
    LD_PRESENCE_OFFLINE = 3, ///< "offline"
    LD_PRESENCE_INVISIBLE = 4 ///< "invisible"
};

/**
 * @brief Activity flags enum type
 *
 * enum values are meant to be OR'd together
 *
 * <a href="https://discordapp.com/developers/docs/topics/gateway#activity-object-activity-flags" Discord API Documentation</a>
 */
enum ld_activity_flags {
    LD_ACTIVITY_FLAG_INSTANCE = 1 << 0,
    LD_ACTIVITY_FLAG_JOIN = 1 << 1,
    LD_ACTIVITY_FLAG_SPECTATE = 1 << 2,
    LD_ACTIVITY_FLAG_JOIN_REQUEST = 1 << 3,
    LD_ACTIVITY_FLAG_SYNC = 1 << 4,
    LD_ACTIVITY_FLAG_PLAY = 1 << 5

};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
#pragma mark Struct declarations
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/**
 * @brief decoded snowflake struct
 *
 * <a href="https://discordapp.com/developers/docs/reference#snowflakes" Discord API Documentation</a>
 */
struct ld_json_snowflake {
    unsigned long long timestamp; ///< milliseconds since the first second of 2015, aka Discord epoch
    unsigned long long worker_id; ///< internal worker ID
    unsigned long long process_id; ///< internal process ID
    unsigned long long increment; ///< incremented for every generated snowflake on that process
};

/**
 * @brief Status update
 *
 * <a href="https://discordapp.com/developers/docs/topics/gateway#update-status-gateway-status-update-structure" Discord API Documentation </a>
 */
struct ld_json_status_update {
//    struct ld_json_user *user; // no longer in the discord API documentation
    LD_SNOWFLAKE *roles; ///< array of snowflakes, no longer in the discord API documentation?
    struct ld_json_activity *game; ///< nullable field
    LD_SNOWFLAKE guild_id; // no longer in the discord API documentation?
    enum ld_json_status_type status;
    int since; ///< nullable field
    int afk; ///< boolean
};

/**
 * @brief Identify connection properties json object
 *
 * <a href="https://discordapp.com/developers/docs/topics/gateway#identify-identify-connection-properties" Discord API Documentation </a>
 */
struct ld_json_identify_connection_properties {
    char *os;
    char *browser;
    char *device;
};

/**
 * @brief Identify json object
 * sent with opcode 2 payloads (IDENTIFY)
 *
 * <a href="https://discordapp.com/developers/docs/topics/gateway#identify-identify-structure" Discord API Documentation </a>
 *
 */
struct ld_json_identify {
    char *token; ///< auth token
    struct ld_json_identify_connection_properties *properties;
    int compress; ///< optional field
    int large_threshold; ///< optional field
    int shard[2]; ///< [shard id, number of shards]
    struct ld_json_status_update *status_update; ///< optional field
};

/**
 * @brief Party json object
 *
 * <a href="https://discordapp.com/developers/docs/topics/gateway#activity-object-activity-party" Discord API Documentation </a>
 *
 */
struct ld_json_party {
    char *id; ///< optional
    int size[2]; ///< optional
};

/**
 * @brief Activity assets json object
 *
 * <a href="https://discordapp.com/developers/docs/topics/gateway#activity-object-activity-assets" Discord API Documentation </a>
 *
 */
struct ld_json_assets {
    char *large_image; ///< optional
    char *large_text; ///< optional
    char *small_image; ///< optional
    char *small_text; ///< optional
};

/**
 * @brief Activity json object
 * bots may only send name, type, and optionally url
 *
 * <a href="https://discordapp.com/developers/docs/topics/gateway#activity-object-activity-structure" Discord API Documentation </a>
 *
 */
struct ld_json_activity {
    char *name;
    enum ld_presence_activity_type type;
    char *url; ///< optional and nullable
    struct ld_json_timestamps *timestamps; ///< optional
    LD_SNOWFLAKE application_id; ///< optional
    char *details; ///< optional and nullable
    char *state; ///< optional and nullable
    struct ld_json_party *party; ///< optional
    struct ld_json_assets *assets; ///< optional
    struct ld_json_secrets *secrets; ///< optional
    int flags; ///optional, OR'd activity flag enums
};

/**
 * @brief Activity secrets json object
 *
 * <a href="https://discordapp.com/developers/docs/topics/gateway#activity-object-activity-secrets" Discord API Documentation </a>
 *
 */
struct ld_json_secrets {
    char *join; ///< optional
    char *spectate; ///< optional
    char *match; ///< optional
};

/**
 * @brief Gateway status update json object
 *
 * <a href="https://discordapp.com/developers/docs/topics/gateway#update-status-gateway-status-update-structure" Discord API Documentation </a>
 */

struct ld_json_gateway_update_status {
    int since; ///< nullable
    struct ld_json_activity *game; ///< nullable
    char *status;
    int afk;
};

struct ld_json_user {
    LD_SNOWFLAKE id;
    char *username;
    char *discriminator; //4 digit tag
    char *avatar;
    int bot; //boolean
    int mfa_enabled; //boolean
    char *locale;
    int verified; //boolean (email verification)
    char *email;
};

struct ld_json_role {
    LD_SNOWFLAKE id;
    char *name;
    int color; //integer representation of hex color code
    int hoist; //boolean
    int position;
    int permissions; //bitfield
    int managed; //boolean
    int mentionable;
};

struct ld_json_attachemnt {
    LD_SNOWFLAKE id;
    char *filename;
    int size;
    char *url;
    char *proxy_url;
    int height;
    int width;
};

struct ld_json_embed_footer {
    char *text;
    char *icon_url;
    char *proxy_icon_url;
};

struct ld_json_embed_image {
    char *url;
    char *proxy_url;
    int height;
    int width;
};

struct ld_json_embed_thumbnail {
    char *url;
    char *proxy_url;
    int height;
    int width;
};

struct ld_json_embed_video {
    char *url;
    int height;
    int width;
};

struct ld_json_embed_provider {
    char *name;
    char *url;
};

struct ld_json_embed_author {
    char *name;
    char *url;
    char *icon_url;
    char *proxy_icon_url;
};

struct ld_json_embed_field {
    char *name;
    char *value;
    int _inline; //bool
};

struct ld_json_embed {
    char *title;
    char *type;
    char *description;
    char *url;
    char *timestamp; //ISO8601 formatted string
    int color;
    struct ld_json_embed_footer *footer;
    struct ld_json_embed_image *image;
    struct ld_json_embed_thumbnail *thumbnail;
    struct ld_json_embed_video *video;
    struct ld_json_embed_provider *provider;
    struct ld_json_embed_author *author;
    struct ld_json_embed_field *fields[];
};

struct ld_json_emoji {
    LD_SNOWFLAKE id;
    char *name;
    struct ld_json_role **roles; //pointer to array of pointers
    struct ld_json_user *user;
    int require_colons;
    int managed;
    int animated;
};

struct ld_json_reaction {
    int count;
    int me; //boolean
    struct ld_json_emoji *emoji; //from the documentation: "partion emoji object type"
};

struct ld_json_message_activity {
    int type;
    char *party_id;
};

struct ld_json_message_application {
    LD_SNOWFLAKE id;
    char *cover_image;
    char *description;
    char *icon;
    char *name;
};

struct ld_json_message {
    LD_SNOWFLAKE id;
    LD_SNOWFLAKE channel_id;
    struct ld_json_user *author;
    char *content;
    TIMESTAMP timestamp; //ISO 8601 formatted string
    TIMESTAMP edited_timestamp; //ISO 8601 formatted string
    int tts; //boolean
    int mention_everyone; //boolean
    struct ld_json_user **mentions; //array of user objects. NOTE: last pointer in array is a null pointer
    struct ld_json_role **mention_roles;
    struct ld_json_attachemnt **attachments;
    struct ld_json_embed **embeds;
    struct ld_json_reaction **reactions;
    LD_SNOWFLAKE webhook_id;
    int type;
    struct ld_json_message_activity *activity;
    struct ld_json_message_application *application;
};

struct ld_json_overwrite {
    LD_SNOWFLAKE id;
    char *type;
    int allow;
    int deny;
};

struct ld_json_attachment {
    LD_SNOWFLAKE id;
    char *filename;
    int size;
    char *url;
    char *proxy_url;
    int height;
    int width;
};

struct ld_json_channel {
    LD_SNOWFLAKE id;
    int type;
    LD_SNOWFLAKE guild_id;
    int position;
    struct ld_json_overwrite **permission_overwrites;
    char *name;
    char *topic;
    int nsfw; //boolean
    LD_SNOWFLAKE last_message_id;
    int bitrate;
    int user_limit;
    struct ld_json_user **recipients;
    char *icon;
    LD_SNOWFLAKE owner_id;
    LD_SNOWFLAKE application_id;
    LD_SNOWFLAKE parent_id;
    TIMESTAMP last_pin_timestamp; //ISO8601 formatted string
};

struct ld_json_voice_state {
    LD_SNOWFLAKE guild_id;
    LD_SNOWFLAKE channel_id;
    LD_SNOWFLAKE user_id;
    char *session_id; //documentation lists as string type
    int deaf; //boolean
    int mute; //boolean
    int self_deaf; //boolean
    int self_mute; //boolean
    int supress; //boolean
};

struct ld_json_guild_member {
    struct ld_json_user *user;
    char *nick;
    LD_SNOWFLAKE *roles; //array of ints
    TIMESTAMP joined_at; //ISO8601 formatted timestamp;
    int deaf; //boolean
    int mute; //boolean
};

struct ld_json_guild {
    LD_SNOWFLAKE id;
    char *name;
    char *icon;
    char *splash;
    int owner;
    LD_SNOWFLAKE owner_id;
    int permissions;
    char *region;
    LD_SNOWFLAKE afk_channel_id;
    int afk_timeout;
    int embed_enabled; //bool
    LD_SNOWFLAKE embed_channel_id;
    int verification_level;
    int default_message_notifications;
    int explicit_content_filter;
    struct ld_json_role **roles;
    struct ld_json_emoji **emojis;
    char **features; //array of strings
    int mfa_level;
    LD_SNOWFLAKE application_id;
    int widget_enabled; //boolean
    LD_SNOWFLAKE widget_channel_id;
    LD_SNOWFLAKE system_channel_id;
    TIMESTAMP joined_at; //ISO8601 timestamp formatted string
    int large; //boolean
    int unavailable; //boolean
    int member_count;
    struct ld_json_voice_state **voice_states;
    struct ld_json_guild_member **members;
    struct ld_json_channel **channels;
    struct ld_json_status_update **presences;
};

struct ld_json_account {
    LD_SNOWFLAKE id; //discord API documentation lists this as a string type
    char *name;
};

struct ld_json_ban {
    char *reason;
    struct ld_json_user *user;
};

struct ld_json_integration {
    LD_SNOWFLAKE id;
    char *name;
    char *type;
    int enabled; //boolean
    int syncing; //boolean
    LD_SNOWFLAKE role_id;
    int expire_behavior;
    int expire_grace_period;
    struct ld_json_user *user;
    struct ld_json_account *account;
    char *synced_at;
};

struct ld_json_getgateway {
    char *url; ///< /gateway url
};

struct ld_json_getgateway_bot {
    char *url;
    int shards;
    struct ld_json_getgateway_bot_sessionstartlimit *limits;
};


struct ld_json_getgateway_bot_sessionstartlimit {
    int total;
    int remaining;
    int reset_after;
};

/*
 * takes four json_t objects and creates a payload
 */
json_t *ld_json_create_payload(json_t *op, json_t *d, json_t *t, json_t *s);

/*
 * creates a Discord message object
 */
json_t *ld_json_create_message();

//todo: snowflake conversion functions
uint64_t ld_snowflake_str2num();
char *ld_snowflake_num2str(LD_SNOWFLAKE flake);
json_t *ld_json_dump_activity(struct ld_json_activity *activity);
int ld_json_load_user(struct ld_json_user *new_user, json_t *user);
json_t *ld_json_unpack_user(struct ld_json_user *user);
json_t *ld_json_unpack_status_update(struct ld_json_status_update *status_update);
json_t *ld_json_unpack_identify_connection_properties(struct ld_json_identify_connection_properties *properties);
json_t *ld_json_unpack_identify(struct ld_json_identify *identify);
const char *ld_json_status2str(enum ld_json_status_type type);
int ld_json_message_init(struct ld_json_message *message);
int ld_json_message_cleanup(struct ld_json_message *message);
int *ld_json_pack_message(struct ld_json_message *new_message, json_t *message);
int ld_json_pack_snowflake(struct ld_json_snowflake *new_flake, LD_SNOWFLAKE snowflake);

#endif //LIBDISCORD_JSON_H
