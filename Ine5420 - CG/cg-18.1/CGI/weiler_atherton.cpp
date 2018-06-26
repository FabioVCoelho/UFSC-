#include "weiler_atherton.h"

using wpset = WeilerAtherton::wpset;
using WAVertex = WeilerAtherton::WAVertex;

std::vector<WAVertex> m_waVertexWindow{
	WAVertex(window_point_t{ -1,-1 }),
	WAVertex(window_point_t{ -1,1 }),
	WAVertex(window_point_t{ 1,1 }),
	WAVertex(window_point_t{ 1,-1 })
};

bool isOutside(const point_t& p) { return (p[0] < -1 || p[0] > 1 || p[1] < -1 || p[1] > 1); }

bool isNotInside(const point_t& p) { return (p[0] <= -1 || p[0] >= 1 || p[1] <= -1 || p[1] >= 1); }

// check if point p1 is before point p2 in a clockwise orientation starting in (-1, -1)
// assumes p1 and p2 are both points at a normalized window border
bool previousInWindowClockwise(const WAVertex * const &  v1, const WAVertex * const &  v2) {
	const window_point_t& p1 = v1->point();
	const window_point_t& p2 = v2->point();
	bool b1 = p1[1] < p1[0];
	bool b2 = p2[1] < p2[0];
	bool b3 = (p2[1] + p2[0]) > (p1[1] + p1[0]);
	bool b4 = (p2[1] + p2[0]) == (p1[1] + p1[0]);
	return ((!b1 && b2) || !(b1 || b2 || !b3) || (b1 && b2 && !b3 && !b4));
}


// check if point p1 is before point p2 in an anticlockwise orientation starting in (-1, -1)
// assumes p1 and p2 are both points at a normalized window border
bool previousInWindowAntiClockwise(const WAVertex * const &  v1, const WAVertex * const &  v2) {
	const window_point_t& p1 = v1->point();
	const window_point_t& p2 = v2->point();
	bool b1 = p1[1] < p1[0];
	bool b2 = p2[1] < p2[0];
	bool b3 = (p2[1] + p2[0]) > (p1[1] + p1[0]);
	bool b4 = (p2[1] + p2[0]) == (p1[1] + p1[0]);
	return ((b1 && !b2) || !(b1 || b2 || b3 || b4) || (b1 && b2 && b3));
}

int enclosed(const window_points_t& windowpoints) {
	bool aboveymax = false, belowymin = false, leftxmin = false, rightxmax = false;
	bool insidewindow = false;
	for (auto& point : windowpoints) {
		if (!isNotInside(point)) {
			return 1;
		}
		aboveymax = aboveymax ? true : point[1] > 1;
		belowymin = belowymin ? true : point[1] < -1;
		leftxmin = leftxmin ? true : point[0] < -1;
		rightxmax = rightxmax ? true : point[0] > 1;
		if (aboveymax && belowymin && leftxmin && rightxmax) {
			return -1;
		}
	}

	return 0;
}

void insertIncoming(
	window_point_t& point,
	wpset& windowPointsList,
	std::list<WAVertex*>& clippedPointsList,
	std::vector<WAVertex>& incoming,
	const std::list<WAVertex*>::iterator& it
)
{
	incoming.push_back(WAVertex(point, it));
	auto it1 = (it == clippedPointsList.begin() ? (--clippedPointsList.end()) : std::prev(it));
	(*it1)->next() = &(incoming.back());
	clippedPointsList.insert(it, &(incoming.back()));
	(*it1)->nextinpolylist() = std::prev(it);
	auto it2 = windowPointsList.emplace(&(incoming.back()));
	auto it3 = (it2 == windowPointsList.begin() ? (--windowPointsList.end()) : std::prev(it2));
	(*it3)->next() = &(incoming.back());
	incoming.back().next() = *it;
}

void insertOutgoing(
	window_point_t& point,
	wpset& windowPointsList,
	std::list<WAVertex*>& clippedPointsList,
	std::vector<WAVertex>& outgoing,
	const std::list<WAVertex*>::iterator& it
)
{
	outgoing.push_back(WAVertex(point));
	auto it1 = (it == clippedPointsList.begin() ? (--clippedPointsList.end()) : std::prev(it));
	(*it1)->next() = &(outgoing.back());
	clippedPointsList.insert(it, &(outgoing.back()));
	(*it1)->nextinpolylist() = std::prev(it);
	auto it2 = windowPointsList.emplace(&(outgoing.back()));
	outgoing.back().next() =
		*(std::next(it2) == windowPointsList.end() ? windowPointsList.begin() : std::next(it2));
}

void addIntersections(
	const window_edges_t& edges,
	wpset& windowPointsList,
	std::list<WAVertex*>& clippedPointsList,
	std::vector<WAVertex>& incoming,
	std::vector<WAVertex>& outgoing
)
{
	bool inside = !isOutside(edges[0].v1());

	std::list<WAVertex*>::iterator it = clippedPointsList.begin();

	for (size_t i = 0; i < edges.size(); ++i) {
		it == --clippedPointsList.end() ? it = clippedPointsList.begin() : ++it;

		if (!isOutside(edges[i].v2()) && inside) {
			continue;
		}

		inside = !isOutside(edges[i].v2());

		const window_point_t& point1 = edges[i].v1();
		const window_point_t& point2 = edges[i].v2();

		double p1 = -(point2[0] - point1[0]);
		double p2 = -p1;
		double p3 = -(point2[1] - point1[1]);
		double p4 = -p3;
		double q1 = point1[0] + 1;
		double q2 = 1 - point1[0];
		double q3 = point1[1] + 1;
		double q4 = 1 - point1[1];

		double u1max = 0, u2min = 1;

		if (p1 == 0) {
			if (q1 < 0 || q2 < 0) {
				continue;
			}
			if ((point1[1] < -1 && point2[1] < -1) || (point1[1] > 1 && point2[1] > 1)) {
				continue;
			}

			if (isOutside(point1)) {
				double xn1 = point1[0];
				double yn1 = (point1[1] < -1 ? -1 : (point1[1] > 1 ? 1 : point1[1]));
				window_point_t newwp(xn1, yn1);
				insertIncoming(newwp, windowPointsList, clippedPointsList, incoming, it);
			}

			if (isOutside(point2)) {
				double xn2 = point2[0];
				double yn2 = (point2[1] < -1 ? -1 : (point2[1] > 1 ? 1 : point2[1]));
				window_point_t newwp(xn2, yn2);
				insertOutgoing(newwp, windowPointsList, clippedPointsList, outgoing, it);
			}
			continue;
		}

		if (p3 == 0) {
			if (q3 < 0 || q4 < 0) {
				continue;
			}
			if ((point1[0] < -1 && point2[0] < -1) || (point1[0] > 1 && point2[0] > 1)) {
				continue;
			}

			if (isOutside(point1)) {
				double yn1 = point1[1];
				double xn1 = (point1[0] < -1 ? -1 : (point1[0] > 1 ? 1 : point1[0]));
				window_point_t newwp(xn1, yn1);
				insertIncoming(newwp, windowPointsList, clippedPointsList, incoming, it);
			}

			if (isOutside(point2)) {
				double yn2 = point2[1];
				double xn2 = (point2[0] < -1 ? -1 : (point2[0] > 1 ? 1 : point2[0]));
				window_point_t newwp(xn2, yn2);
				insertOutgoing(newwp, windowPointsList, clippedPointsList, outgoing, it);
			}
			continue;
		}

		if (p1 != 0) {
			double r1 = q1 / p1;
			double r2 = q2 / p2;
			u1max = p1 < 0 ? (r1 > u1max ? r1 : u1max) : (r2 > u1max ? r2 : u1max);
			u2min = p1 < 0 ? (r2 < u2min ? r2 : u2min) : (r1 < u2min ? r1 : u2min);
		}
		if (p3 != 0) {
			double r3 = q3 / p3;
			double r4 = q4 / p4;
			u1max = p3 < 0 ? (r3 > u1max ? r3 : u1max) : (r4 > u1max ? r4 : u1max);
			u2min = p3 < 0 ? (r4 < u2min ? r4 : u2min) : (r3 < u2min ? r3 : u2min);
		}

		if (u1max > u2min) {
			continue;
		}

		if (isOutside(point1)) {
			double xn1 = point1[0] + p2 * u1max;
			double yn1 = point1[1] + p4 * u1max;
			window_point_t newwp(xn1, yn1);
			insertIncoming(newwp, windowPointsList, clippedPointsList, incoming, it);
		}

		if (isOutside(point2)) {
			double xn2 = point1[0] + p2 * u2min;
			double yn2 = point1[1] + p4 * u2min;
			window_point_t newwp(xn2, yn2);
			insertOutgoing(newwp, windowPointsList, clippedPointsList, outgoing, it);
		}
	}
}

void clip(const edgevertex2f_t& windowShape, edgevertex2f_t& clippedShape, bool clockwise) {

	window_edges_t& clippedEdges = clippedShape.edges();
	window_points_t& clippedPoints = clippedShape.vertices();

	const window_points_t& points = windowShape.vertices();
	const window_edges_t& edges = windowShape.edges();

	clippedPoints.clear();
	clippedEdges.clear();
	clippedPoints.reserve(2 * edges.size());

	decltype(&previousInWindowClockwise) comp = clockwise ?
		&previousInWindowClockwise : &previousInWindowAntiClockwise;

	wpset waVertexWindowList(comp);
	for (auto& wavertex : m_waVertexWindow) {
		waVertexWindowList.emplace(&wavertex);
		wavertex.visited() = false;
	}

	std::list<WAVertex*> waVertexList;
	std::vector<WAVertex> waVertexHolder;

	size_t numVertices = points.size();

	waVertexHolder.reserve(2 * numVertices);
	for (auto point : points) {
		waVertexHolder.emplace_back(WAVertex(point));
		waVertexList.emplace_back(&(waVertexHolder.back()));
	}
	std::vector<WAVertex> incoming;
	std::vector<WAVertex> outgoing;
	incoming.reserve(points.size());
	outgoing.reserve(points.size());

	for (size_t i = 0; i < numVertices - 1; ++i) {
		waVertexHolder[i].next() = &(waVertexHolder[i + 1]);
	}
	waVertexHolder[numVertices - 1].next() = &(waVertexHolder[0]);
	for (size_t i = 0; i < 3; ++i) {
		m_waVertexWindow[i].next() = &(m_waVertexWindow[i + 1]);
	}
	m_waVertexWindow[3].next() = &(m_waVertexWindow[0]);

	addIntersections(edges, waVertexWindowList, waVertexList, incoming, outgoing);

	if (waVertexList.size() == points.size()) {
		int enc = enclosed(points);
		if (enc == 1) {
			clippedShape.reset(points);
			return;
		}
		if (enc == -1) {
			clippedShape.reset(std::vector<Vec<2, double>>{ { -1, -1 }, { -1, 1 }, { 1, 1 }, { 1, -1 } });
		}
		return;
	}

	WAVertex* current;
	size_t inserted = 0, totalInserted = 0;
	for (auto& inc : incoming) {
		if (inc.visited()) {
			continue;
		}
		inc.visit();
		clippedPoints.emplace_back(inc.point());
		++inserted;
		current = *(inc.nextinpolylist());
		for (;;) {
			if (current->visited()) {
				for (size_t i = totalInserted; i < inserted - 1; ++i) {
					clippedEdges.emplace_back(clippedPoints[i], clippedPoints[i + 1]);
				}
				clippedEdges.emplace_back(clippedPoints[inserted - 1], clippedPoints[totalInserted]);
				totalInserted = inserted;
				break;
			}
			current->visit();
			clippedPoints.emplace_back(current->point());
			++inserted;
			current = current->next();
		}
	}

	return;
}

void WeilerAtherton::clip(const edgevertex2f_t& windowShape, edgevertex2f_t& clippedShape) {
	unit xmin = std::numeric_limits<double>::infinity();
	size_t idx = 0;
	const window_points_t& points = windowShape.vertices();
	for (size_t i = 0; i < points.size(); ++i) {
		xmin = points[i][0] <= xmin ?
			((idx = points[i][1] < points[idx][0] ? i : idx), points[i][0]) : xmin;
	}
	size_t ia = (idx - 1) % points.size();
	size_t ib = idx;
	size_t ic = (idx + 1) % points.size();

	bool clockwise = (
		((points[ib][0] - points[ia][0]) * (points[ic][1] - points[ia][1])) -
		((points[ic][0] - points[ia][0]) * (points[ib][1] - points[ia][1]))
		) < 0;

	::clip(windowShape, clippedShape, clockwise);
	return;
}

