#ifndef EVENTS_HPP
#define EVENTS_HPP

// events
struct play {};
struct end_pause {};
struct stop {};
struct pause {};
struct open_close {};

// A "complicated" event type that carries some data.
enum DiskTypeEnum
{
    DISK_CD=0,
    DISK_DVD=1
};
struct cd_detected
{
    cd_detected(std::string name, DiskTypeEnum diskType)
        : name(name),
        disc_type(diskType)
    {}

    std::string name;
    DiskTypeEnum disc_type;
};


#endif