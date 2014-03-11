#pragma once
#include <vector>

#include <Core/EigenTypedef.h>
#include <Misc/Triplet.h>

#include "IndexHeap.h"

class ShortEdgeRemoval {
    public:
        ShortEdgeRemoval(MatrixFr& vertices, MatrixIr& faces);

    public:
        /**
         * Remove all edges that <= thresold
         * If thresold=0, remove all degenerated edges.
         */
        size_t run(Float threshold);
        MatrixFr get_vertices() const;
        MatrixIr get_faces() const;

    private:
        typedef Triplet Edge;

        void init();
        void update();
        void init_vertex_map();
        void init_edges();
        void init_edge_length_heap();
        void update_faces();
        void collapse(Float threshold);
        bool edge_is_valid(size_t edge_idx) const;
        void collapse_edge(size_t edge_idx);
        VectorF get_vertex(size_t i) const;
        Float min_edge_length() const;
        Float compute_edge_length(const Edge& e) const;
        size_t get_num_vertices() const;
        size_t get_num_faces() const;
        size_t get_dim() const;

    private:
        std::vector<size_t> m_vertex_map;
        std::vector<Edge> m_edges;
        IndexHeap<Float> m_heap;

        MatrixFr m_vertices;
        MatrixIr m_faces;

        std::vector<VectorF> m_new_vertices;

        size_t m_num_collapsed;

    private:
        static const size_t UNMAPPED;
};