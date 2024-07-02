#pragma once

#include <core.hpp>
#include <renderer_interface.hpp>
#include <serializable.hpp>

namespace bolt
{
    typedef std::vector<ref_ptr<RenderInterface>>::iterator SceneIterator;

    class Scene : public Serializable
    {
        public:
            [[nodiscard]] const ref_ptr<RenderInterface>& get_object(uint32_t id);

            [[nodiscard]] uint32_t add_object(ref_ptr<RenderInterface> object);

            void remove(uint32_t id);

            void draw();

            ref_ptr<Serializable> deserialize(std::string input) override;

            std::string serialize() override;
        private:
            std::vector<ref_ptr<RenderInterface>> objects;
    };
}