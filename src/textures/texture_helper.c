#include "../include/texture_helper.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

t_texture	*load(t_texture *this, char *texture_path)
{
	if (!(this->data = stbi_load(texture_path, &this->w, &this->h, &this->channels, 0)))
	{
		this->error = 1;
		printf("ERROR::STBI::COULD_NOT_LOAD_IMAGE : %s\n", texture_path);
	}
	return (this);
}

/*
** texture_number starts from 0: is used to load multiple textures on GPU
** gl_tex_target GL_TEXTURE_2D GL_TEXTURE_3D etc..
*/

t_texture	*bind(t_texture *this, int gl_tex_target, int texture_unit)
{
	glGenTextures(1, &this->gl_id);
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(gl_tex_target, this->gl_id);
	this->gl_target = gl_tex_target;
	return (this);
}

t_texture	*set_params(t_texture *this, t_tex_params opts)
{
	if (this->gl_target == -1)
	{
		this->error = 1;
		printf("ERROR::TEXTURE::NO_BIND_TARGET\n");
	}
	else
	{
		if (opts.wrap_s)
			glTexParameteri(this->gl_target, GL_TEXTURE_WRAP_S, opts.wrap_s);	// set how openGL wraps textures on S axis (x)
		if (opts.wrap_t)
			glTexParameteri(this->gl_target, GL_TEXTURE_WRAP_T, opts.wrap_t);
		if (opts.wrap_r)
			glTexParameteri(this->gl_target, GL_TEXTURE_WRAP_R, opts.wrap_r);
		if (opts.filter_min)
			glTexParameteri(this->gl_target, GL_TEXTURE_MIN_FILTER, opts.filter_min); // texture filterng option for when using small texture on bigger obj
		if (opts.filter_mag)
			glTexParameteri(this->gl_target, GL_TEXTURE_MAG_FILTER, opts.filter_mag);
	}
	return (this);
}

int			exec(t_texture *this)
{
	if (this->error == 1 || !this->data)
	{
		printf("ERROR::TEXTURE::EXEC\n");
		return (0);
	}
	else
	{
		glTexImage2D(this->gl_target, 0, GL_RGB, this->w, this->h, 0, this->channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, this->data); // generates texture on currently bound texture obj
		glGenerateMipmap(this->gl_target); // saves us form calling glTexImage2D(GL_TEXTURE_2D, 0, ...) for different levels(0)
		stbi_image_free(this->data);
		this->data = NULL;
		return (1);
	}
}

void		tex_destroy(t_texture **this)
{
	if (*this == NULL)
		return ;
	if ((*this)->data)
		free((*this)->data);
	free(*this);
	*this = NULL;
}

t_texture	*texture_construct()
{
	t_texture *this;

	// stbi_set_flip_vertically_on_load(1);
	if(!(this = (t_texture *)malloc(sizeof(t_texture))))
		return(NULL);
	this->error = 0;
	this->gl_target = -1;
	this->load = &load;
	this->bind = &bind;
	this->set_params = &set_params;
	this->exec = &exec;
	this->destroy = &tex_destroy;
	return (this);
}





//--------------------------------
	// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // only after enabling MIPMAP with glGenerateMipmaps()
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); // sets how OpenGL handles filtering between different mipmap layers

/*int width, height, nrChannels;
unsigned char *tex_data;
char *texture_path = "texture/container.jpg";

unsigned int texture;
if (tex_data = stbi_load(texture_path, &width, &height, &nrChannels, 0))
{
	printf("nrChannels %d\n", nrChannels);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set how openGL wraps textures on S axis (x)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // texture filterng option for when using small texture on bigger obj
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data); // generates texture on currently bound texture obj
	glGenerateMipmap(GL_TEXTURE_2D); // saves us form calling glTexImage2D(GL_TEXTURE_2D, 0, ...) for different levels(0)

	stbi_image_free(tex_data);
}
else
{
	printf("ERROR::STBI::COULD_NOT_LOAD_IMAGE : %s\n", texture_path);
	return (-1);
}*/