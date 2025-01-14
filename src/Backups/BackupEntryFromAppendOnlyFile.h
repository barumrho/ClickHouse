#pragma once

#include <Backups/BackupEntryFromImmutableFile.h>


namespace DB
{

/// Represents a file prepared to be included in a backup, assuming that until this backup entry is destroyed
/// the file can be appended with new data, but the bytes which are already in the file won't be changed.
class BackupEntryFromAppendOnlyFile : public BackupEntryFromImmutableFile
{
public:
    BackupEntryFromAppendOnlyFile(
        const DiskPtr & disk_,
        const String & file_path_,
        const std::optional<UInt64> & file_size_ = {},
        const std::optional<UInt128> & checksum_ = {},
        const std::shared_ptr<TemporaryFileOnDisk> & temporary_file_ = {});

    UInt64 getSize() const override { return limit; }
    std::unique_ptr<SeekableReadBuffer> getReadBuffer() const override;

private:
    const UInt64 limit;
};

}
