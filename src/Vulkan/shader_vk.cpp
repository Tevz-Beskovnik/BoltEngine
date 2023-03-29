#include <shader_vk.hpp>

namespace bolt
{
    [[nodiscard]] ShaderVK::ShaderVK(const_str shader_location, shader_type type)
    {
        ;
    }

    ShaderVK::~ShaderVK()
    {
        ;
    }

    [[nodiscard]] ref_ptr<ShaderVK> ShaderVK::create(const_str shader_location, shader_type type)
    {
        return create_ref<ShaderVK>(shader_location, type);
    }

    void ShaderVK::bind()
    {

    }

    void ShaderVK::unbind()
    {

    }

    void ShaderVK::destroy()
    {

    }
}