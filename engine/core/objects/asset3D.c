#include "asset3D.h"

asset3D load_obj_file(const char* obj_file) {

  // import
  const struct aiScene* scene = aiImportFile(obj_file,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_SortByPType);

  // If the import failed, report it
  if(!scene)
  {
    printf("%s\n", aiGetErrorString());
    return (asset3D){NULL, 0, NULL, 0, (render_attribs){NULL, 0}};
  }

  // Now we can access the file's contents
  float* verts;
  unsigned int* inds;
  unsigned int nverts = 0;
  unsigned int ninds = 0;
  render_elem* e = (render_elem*)malloc(3 * sizeof(render_elem));
  e[0] = (render_elem){VERT, 3};
  e[1] = (render_elem){NORMAL, 3};
  e[2] = (render_elem){TEX_COORD, 2};
  render_attribs attribs = attrib_list(e, 3);

  int stride = 8;

  for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
      nverts += scene->mMeshes[i]->mNumVertices;
      for (unsigned int j = 0; j < scene->mMeshes[i]->mNumFaces; ++j) {
          ninds += scene->mMeshes[i]->mFaces[j].mNumIndices;
      }
  }

  verts = (float*)malloc(nverts * stride * sizeof(float));
  inds = (unsigned int*)malloc(ninds * sizeof(unsigned int));

  int data_index = 0;
  int ind_index = 0;
  int texture_index = 0;
  for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
      for (unsigned int j = 0; j < scene->mMeshes[i]->mNumVertices; ++j) {
          verts[data_index] = scene->mMeshes[i]->mVertices[j].x;
          verts[data_index + 1] = scene->mMeshes[i]->mVertices[j].y;
          verts[data_index + 2] = scene->mMeshes[i]->mVertices[j].z;
          data_index += 3;

          if (scene->mMeshes[i]->mNormals != NULL) {
              verts[data_index] = scene->mMeshes[i]->mNormals[j].x;
              verts[data_index + 1] = scene->mMeshes[i]->mNormals[j].y;
              verts[data_index + 2] = scene->mMeshes[i]->mNormals[j].z;
              data_index += 3;
          }

          if (scene->mMeshes[i]->mTextureCoords[texture_index] != NULL) {
              verts[data_index] = scene->mMeshes[i]->mTextureCoords[texture_index][j].x;
              verts[data_index + 1] = scene->mMeshes[i]->mTextureCoords[texture_index][j].y;
              data_index += 2;
          }
      }

      for (unsigned int j = 0; j < scene->mMeshes[i]->mNumFaces; ++j) {
          for (unsigned int k = 0; k < scene->mMeshes[i]->mFaces[j].mNumIndices; ++k) {
              inds[ind_index] = scene->mMeshes[i]->mFaces[j].mIndices[k];
              ++ind_index;
          }
      }
  }

  // We're done. Release all resources associated with this import
  aiReleaseImport(scene);

  return (asset3D){verts, nverts, inds, ninds, attribs};
}

void delete_asset3D(asset3D asset) {
    free(asset.verts);
    free(asset.inds);
    free(asset.attribs.elems);
}
