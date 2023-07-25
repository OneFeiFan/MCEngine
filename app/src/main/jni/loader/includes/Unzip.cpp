//
// Created by 30225 on 2023/7/25.
//
#include "Unzip.h"
#include "headers/miniz.h"
#include <filesystem>
#include <fstream>

void UnZip(const char *s_Test_archive_filename)
{
    mz_bool status;
    auto *zip_archive = new mz_zip_archive();
    void *p;
    namespace fs = std::filesystem;
    //memset(&zip_archive, 0, sizeof(zip_archive));
    status = mz_zip_reader_init_file(zip_archive, s_Test_archive_filename, 0);
    if(!status){
        printf("mz_zip_reader_init_file() failed!\n");
        return;
    }
    fs::remove_all("/data/data/com.mojang.minecraftpe/MCEngine/");
    for(int i = 0; i < (int) mz_zip_reader_get_num_files(zip_archive); ++i){
        mz_zip_archive_file_stat file_stat;
        if(!mz_zip_reader_file_stat(zip_archive, i, &file_stat)){
            printf("mz_zip_reader_file_stat() failed!\n");
            mz_zip_reader_end(zip_archive);
            return;
        }
        if(!mz_zip_reader_is_file_a_directory(zip_archive, i)){
            p = mz_zip_reader_extract_file_to_heap(zip_archive, file_stat.m_filename, &file_stat.m_uncomp_size, 0);
            if(!p){
                printf("mz_zip_reader_extract_file_to_heap() failed!\n");
                mz_zip_reader_end(zip_archive);
                return;
            }
            std::string directoryName("/data/data/com.mojang.minecraftpe/MCEngine/");
            fs::path path(directoryName + file_stat.m_filename);
            fs::path direction = path.parent_path();
            if(!fs::exists(direction)){
                fs::create_directories(direction);
            }
            std::ofstream ofs(path, std::ios::out | std::ios::binary);
            ofs.write((const char *) p, (int) file_stat.m_uncomp_size);
            ofs.close();
            mz_free(p);
        }
    }
    mz_zip_reader_end(zip_archive);
}