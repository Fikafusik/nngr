
#include "pack.hpp"

namespace nngr {

    void to_json(json& j, const pack_t& pack) {
        j = json{
            { "id", pack.id },
            { "problems", pack.problems }
        };
    }
    void from_json(const json& j, pack_t& pack) {
        j.at("id").get_to(pack.id);
        j.at("problems").get_to(pack.problems);
    }

};
